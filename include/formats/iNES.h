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
#ifndef _FORMATS_INES_H
#define _FORMATS_INES_H

#include <experimental/filesystem>

#include "formats/deserializer.h"

namespace fmt {

class Ines_format : public Deserializer {
 public:
  Ines_format() = default;
  Ines_format(const Ines_format &) = default;
  Ines_format(const Ines_format &&) = delete;
  Ines_format &operator=(const Ines_format &) = default;
  ~Ines_format() = default;

  Rom load_rom(const std::experimental::filesystem::path &p) override;
};
};  // namespace fmt

#endif  // _FORMATS_INES_H
