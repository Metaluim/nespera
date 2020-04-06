/*
   The MIT License (MIT)
   Copyright (c) 2020 Ricardo Ferreira

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/
#ifndef _FORMAT_ROM_H
#define _FORMAT_ROM_H

#include <bits/c++config.h>
#include <memory>

#include "formats/Common.h"

namespace fmt {

class Rom {
 public:
  Rom() = default;
  Rom(const Rom &r) = default;
  Rom(Rom &&r) = default;

  Version m_version;             // the format version
  byte_mem_sptr m_trainer_data;  // cheat data
  byte_mem_sptr m_prg_data;      // the actual game data
  std::size_t m_prg_size;        // the size of game data
  byte_mem_sptr m_chr_data;      // the pattern table data
  std::size_t m_chr_size;        // the size of pattern table data
  byte_mem_sptr m_instrom;       // ???
  byte_mem_sptr m_prom;          // ???
  byte_mem_sptr m_trailer;       // optional section at the end of rom
  bool m_horizontal_mirroring;   // flag determining mirroring type
  bool m_has_prg;                // flag determining whether ROM has PRG
  bool m_ignore_mirroring;       // flag indicating whether or not mirroring
                                 // should be ignored
  bool m_is_pal;                 // flag indicating TV set system of ROM
};
};  // namespace fmt

#endif  // _FORMAT_ROM_H
