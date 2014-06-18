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

#ifndef I18N_ADDRESSINPUT_UTIL_STRING_COMPARE_H_
#define I18N_ADDRESSINPUT_UTIL_STRING_COMPARE_H_

#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

namespace i18n {
namespace addressinput {

class StringCompare {
 public:
  StringCompare();
  ~StringCompare();

  // Returns true if a human reader would consider |a| and |b| to be "the same".
  // Libaddressinput itself isn't really concerned about how this is done. This
  // default implementation just does case insensitive string matching.
  bool NaturalEquals(const std::string& a, const std::string& b) const;

  // Comparison function for use with the STL analogous to NaturalEquals().
  // Libaddressinput itself isn't really concerned about how this is done, as
  // long as it conforms to the STL requirements on less<> predicates. This
  // default implementation is VERY SLOW! Must be replaced if you need speed.
  bool NaturalLess(const std::string& a, const std::string& b) const;

 private:
  class Impl;
  scoped_ptr<Impl> impl_;

  DISALLOW_COPY_AND_ASSIGN(StringCompare);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_UTIL_STRING_COMPARE_H_
