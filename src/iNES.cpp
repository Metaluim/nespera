#include "formats/iNES.h"

#include <experimental/filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>

#include "formats/Common.h"
#include "formats/Exceptions.h"

using namespace fmt;
namespace fs = std::experimental::filesystem;

static const uint INES_FORMAT_MIN_SIZE = 16U;  // We need at least 16 byte for
                                               // format metadata.

static const std::string MAGIC_SEQ = "NES\x1a";  // Magic pattern to look for in
                                                 // header.

static constexpr byte TRAINER_MASK = 1 << 2;  // Mask for obtaining the trainer
                                              // enabled bit of flag 6.

static constexpr byte MIRRORING_MASK = 1 << 0;
static constexpr byte PRG_MASK = 1 << 1;
static constexpr byte IGNORE_MIRRORING_MASK = 1 << 3;
static constexpr byte TV_SYSTEM_MASK = 1 << 0;

Rom Ines_format::load_rom(const fs::path &p) {
  if (!fs::is_regular_file(p))
    throw Loader_exception(p.string() + " is not a valid or readable file");

  // Obtain the file size
  std::ifstream fin(p, std::ios::binary | std::ios::ate);
  if (fin.fail()) throw Loader_exception(p.string() + " couldn't be opened");
  std::streamsize sz = fin.tellg();
  fin.seekg(0, std::ios::beg);
  if (sz < INES_FORMAT_MIN_SIZE || fin.fail())
    throw Loader_exception("Couldn't read " + p.string());

  //
  // Check the magic sequence at the start, to verify if the file is of the
  // correct format.
  //
  auto buf = std::make_unique<byte[]>(MAGIC_SEQ.length() + 1);
  fin.read(reinterpret_cast<char *>(buf.get()), MAGIC_SEQ.length());
  buf[MAGIC_SEQ.length()] = '\0';
  std::string magicSeq(reinterpret_cast<char *>(buf.get()));
  if (magicSeq != MAGIC_SEQ)
    throw Loader_exception(p.string() + " is not a valid .NES file!");

  // Start building the Rom object
  Rom ret;
  ret.m_version = Version::iNES;

  // Load all flags...
  byte num_16kb_banks = 0U;
  byte num_8kb_banks = 0U;
  byte flag6 = 0U;
  byte flag7 = 0U;
  byte flag8 = 0U;
  byte flag9 = 0U;
  fin >> num_16kb_banks;
  fin >> num_8kb_banks;
  fin >> flag6;
  fin >> flag7;
  fin >> flag8;
  fin >> flag9;

  // Configure the Rom object appropriately
  ret.m_horizontal_mirroring = flag6 & MIRRORING_MASK;
  ret.m_has_prg = flag6 & PRG_MASK;
  ret.m_ignore_mirroring = flag6 & IGNORE_MIRRORING_MASK;
  ret.m_is_pal = !(flag9 & TV_SYSTEM_MASK);

  // Skip unused space
  fin.seekg(5, std::ios::cur);

  // Skip the trainer (if present)
  if (flag6 & TRAINER_MASK) {
    fin.seekg(512, std::ios::cur);
  }

  // Load the PRG ROM data (if available)
  if (num_16kb_banks != 0U) {
    size_t bank_sz = 16384 * num_16kb_banks;
    ret.m_prg_data = std::make_shared<byte[]>(bank_sz);
    fin.read(reinterpret_cast<char *>(ret.m_prg_data.get()), bank_sz);
  }

  // Load the CHR ROM data (if available)
  if (num_8kb_banks != 0U) {
    size_t bank_sz = 8191 * num_8kb_banks;
    ret.m_chr_data = std::make_shared<byte[]>(bank_sz);
    fin.read(reinterpret_cast<char *>(ret.m_chr_data.get()), bank_sz);
  }

  return ret;
}
