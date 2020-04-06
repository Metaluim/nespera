#include "formats/Common.h"

#include <iomanip>
#include <ios>
#include <iostream>

using namespace fmt;

//
// Taken from:
// https://codereview.stackexchange.com/questions/165120/printing-hex-dumps-for-diagnostics
//
std::ostream &fmt::dump_hex(std::ostream &os, const byte_mem_sptr &buffer,
                            std::size_t bufsize) {
  if (buffer == nullptr) {
    return os;
  }
  auto oldFormat = os.flags();
  auto oldFillChar = os.fill();
  constexpr std::size_t maxline{8};
  // create a place to store text version of string
  char renderString[maxline + 1];
  char *rsptr{renderString};
  // convenience cast
  const unsigned char *buf{
      reinterpret_cast<const unsigned char *>(buffer.get())};

  for (std::size_t linecount = maxline; bufsize; --bufsize, ++buf) {
    os << std::setw(2) << std::setfill('0') << std::hex
       << static_cast<unsigned>(*buf) << ' ';
    *rsptr++ = std::isprint(*buf) ? *buf : '.';
    if (--linecount == 0) {
      *rsptr++ = '\0';  // terminate string
      os << " | " << renderString;
      os << '\n';
      rsptr = renderString;
      linecount = std::min(maxline, bufsize);
    }
  }
  // emit newline if we haven't already
  if (rsptr != renderString) {
    for (*rsptr++ = '\0'; rsptr != &renderString[maxline + 1]; ++rsptr) {
      os << "   ";
    }
    os << " | " << renderString;
    os << '\n';
  }

  os.fill(oldFillChar);
  os.flags(oldFormat);
  return os;
}
