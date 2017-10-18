// Copyright (C) 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef I18N_ADDRESSINPUT_UTIL_SIZE_H_
#define I18N_ADDRESSINPUT_UTIL_SIZE_H_

#include <cstddef>

namespace i18n {
namespace addressinput {

// A C++11 implementation of the C++17 std::size, copied from the standard:
// https://isocpp.org/files/papers/n4280.pdf

template <class T, size_t N>
constexpr size_t size(const T (&array)[N]) {
  return N;
}

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_UTIL_SIZE_H_
