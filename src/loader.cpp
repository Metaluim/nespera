#include <cstdlib>

#include "formats/Rom.h"
#include "formats/deserializer.h"
#include "formats/iNES.h"

int main(int argc, char **argv) {
  fmt::Ines_format deserializer;
  auto rom = deserializer.load_rom(
      "/home/ricardo/source/nespera/test_roms/Super\ Mario\ World.nes");

  return EXIT_SUCCESS;
}
