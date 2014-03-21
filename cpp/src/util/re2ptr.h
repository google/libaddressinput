// Copyright (C) 2014 Google Inc.
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
//
// Work-around for problems with the RE2 library. Must be the first #include
// statement in the compilation unit. Do not #include in other header files.

#ifndef I18N_ADDRESSINPUT_UTIL_RE2PTR_H_
#define I18N_ADDRESSINPUT_UTIL_RE2PTR_H_

// RE2 will, in some environments, define class RE2 inside namespace re2 and
// then have a public "using re2::RE2;" statement to bring that definition into
// the root namespace, while in other environments it will define class RE2
// directly in the root namespace.
//
// Because of that, it's impossible to write a portable forward declaration of
// class RE2.
//
// In some environments, the #include <re2/re2.h> statement will bring in its
// own definitions of arraysize et al., which in that case would clash with the
// same definitions that libaddressinput has in the util/basictypes.h header
// file.
//
// Because of that, it's undesirable to #include <re2/re2.h> in libaddressinput
// header files (even internal ones).
//
// The work-around in this file works by having #include <re2/re2.h> as the
// first #include statement in the compilation unit, then test whether the
// arraysize macro has been defined by that header file, in which case an
// include guard is defined to prevent util/basictypes.h from getting included
// later, and then wrap pointers to RE2 object in the simple struct RE2ptr,
// which is trivial to forward declare.

#include <re2/re2.h>

#ifdef arraysize
#define I18N_ADDRESSINPUT_UTIL_BASICTYPES_H_
#endif

namespace i18n {
namespace addressinput {

struct RE2ptr {
  RE2ptr(RE2* init_ptr) : ptr(init_ptr) {}
  ~RE2ptr() { delete ptr; }
  RE2* const ptr;
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_UTIL_RE2PTR_H_
