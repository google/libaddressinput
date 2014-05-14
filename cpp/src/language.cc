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

#include "language.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "util/string_split.h"

namespace i18n {
namespace addressinput {

Language::Language(const std::string& language_tag) : tag(language_tag),
                                                      base(),
                                                      has_latin_script(false) {
  // Character '-' is the separator for subtags in the BCP 47. However, some
  // legacy code generates tags with '_' instead of '-'.
  static const char kSubtagsSeparator = '-';
  static const char kAlternativeSubtagsSeparator = '_';
  std::replace(tag.begin(), tag.end(), kAlternativeSubtagsSeparator,
               kSubtagsSeparator);

  // OK to use 'tolower' because BCP 47 tags are always in ASCII.
  std::string lowercase = tag;
  std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(),
                 tolower);

  base = lowercase.substr(0, lowercase.find(kSubtagsSeparator));

  // The lowercase BCP 47 subtag for Latin script.
  static const char kLowercaseLatinScript[] = "latn";
  std::vector<std::string> subtags;
  SplitString(lowercase, kSubtagsSeparator, &subtags);

  // Support only the second and third position for the script.
  has_latin_script =
      (subtags.size() > 1 && subtags[1] == kLowercaseLatinScript) ||
      (subtags.size() > 2 && subtags[2] == kLowercaseLatinScript);
}

Language::~Language() {}

}  // namespace addressinput
}  // namespace i18n
