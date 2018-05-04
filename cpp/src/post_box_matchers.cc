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

#include "post_box_matchers.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

#include <re2/re2.h>

#include "language.h"
#include "rule.h"
#include "util/re2ptr.h"
#include "util/size.h"

namespace i18n {
namespace addressinput {

namespace {

// kLanguageInfoMap is a constant table that associates language names
// with the corresponding matching regexp.
//
// NOTE: This array must be sorted in increasing language name values.
//       this is checked at compile time through a static_assert() below.
struct LanguageInfo {
  const char* language;
  const char* regexp;

  static bool less(const LanguageInfo& a, const LanguageInfo& b) {
      return strcmp(a.language, b.language) < 0;
  }
};

constexpr const LanguageInfo kLanguageInfoMap[] = {
      {"ar", u8R"(صندوق بريد|ص[-. ]ب)"},
      {"cs", u8R"((?i)p\.? ?p\.? \d)"},
      {"da", u8R"((?i)Postboks)"},
      {"de", u8R"((?i)Postfach)"},
      {"el", u8R"((?i)T\.? ?Θ\.? \d{2})"},
      {"en", u8R"(Private Bag|Post(?:al)? Box)"},
      {"es", u8R"((?i)(?:Apartado|Casillas) de correos?)"},
      {"fi", u8R"((?i)Postilokero|P\.?L\.? \d)"},
      {"fr", u8R"((?i)Bo(?:[iî]|î)te Postale|BP \d|CEDEX \d)"},
      {"hr", u8R"((?i)p\.? ?p\.? \d)"},
      {"hu", u8R"((?i)Postafi(?:[oó]|ó)k|Pf\.? \d)"},
      {"ja", u8R"(私書箱\d{1,5}号)"},
      {"nl", u8R"((?i)Postbus)"},
      {"no", u8R"((?i)Postboks)"},
      {"pl", u8R"((?i)Skr(?:\.?|ytka) poczt(?:\.?|owa))"},
      {"pt", u8R"((?i)Apartado)"},
      {"ru", u8R"((?i)абонентский ящик|[аa]"я (?:(?:№|#|N) ?)?\d)"},
      {"sv", u8R"((?i)Box \d)"},
      {"und", u8R"(P\.? ?O\.? Box)"},
      {"zh", u8R"(郵政信箱.{1,5}號|郵局第.{1,10}號信箱)"},
};

constexpr size_t kLanguageInfoMapSize = size(kLanguageInfoMap);
// Compile-time function that returns true iff the content of string |a|
// is less or equal to string |b|.
constexpr bool StrLessOrEqualConstexpr(const char* a, const char* b) {
  return (*a == '\0') ? true : (
      (*a == *b) ? StrLessOrEqualConstexpr(a + 1, b + 1) : (*a < *b));
}

// Sanity checks.
static_assert(StrLessOrEqualConstexpr("", ""), "");
static_assert(StrLessOrEqualConstexpr("", "foo"), "");
static_assert(!StrLessOrEqualConstexpr("foo", ""), "");
static_assert(StrLessOrEqualConstexpr("foo", "foo"), "");
static_assert(!StrLessOrEqualConstexpr("foo", "bar"), "");
static_assert(StrLessOrEqualConstexpr("bar", "foo"), "");
static_assert(StrLessOrEqualConstexpr("foo", "foobar"), "");
static_assert(!StrLessOrEqualConstexpr("foobar", "foo"), "");

// Compile-time function to verify that LanguageInfoMap is properly sorted.
// The |n| parameter is a starting position for the check.
constexpr bool CheckLanguageInfoMapOrderConstexpr(size_t n = 0) {
  // Compare two items at positions |n| and |n + 1| and return false if they
  // are not in the correct order, otherwise, recursively try remaining
  // positions until the end of the array.
  return !StrLessOrEqualConstexpr(kLanguageInfoMap[n].language,
                                  kLanguageInfoMap[n + 1].language) ? false : (
      (n + 2 < kLanguageInfoMapSize) ?
         CheckLanguageInfoMapOrderConstexpr(n + 1) : true);
}

// Compile-time check for the order to kLanguageInfoMap entries.
static_assert(CheckLanguageInfoMapOrderConstexpr(),
              "kLanguageInfoMap is not correctly sorted!");

// Return a pointer to the LanguageInfo entry corresponding to |language|
// or nullptr if this wasn't found.
const LanguageInfo* FindLanguageInfoFor(const std::string& language) {
  const LanguageInfo* begin = kLanguageInfoMap;
  const LanguageInfo* end = begin + kLanguageInfoMapSize;
  LanguageInfo key = { language.c_str(), };
  const LanguageInfo* probe =
      std::lower_bound(begin, end, key, LanguageInfo::less);
  if (probe != end && language == probe->language) {
    return probe;
  }
  return nullptr;
}

// A convenience wrapper class for a fixed array of RE2PlainPtr that shall
// only be instantiated as a static variable.
class StaticRE2Array {
 public:
  StaticRE2Array() {
    // Initialize all re2s_ instance now. Doing this lazily in findMatcherFor()
    // would not be thread-safe, while doing it in the constructor of a static
    // local variable is.
    for (size_t n = 0; n < kLanguageInfoMapSize; ++n) {
      re2s_[n].ptr = new RE2(kLanguageInfoMap[n].regexp);
    }
  }

  ~StaticRE2Array() {
    // Destroy all instances on destruction. Since this is a static variable
    // this will only happen on program exit, or if the library is unloaded
    // at runtime (e.g. through dlclose()).
    for (auto& entry : re2s_) {
      delete entry.ptr;
    }
  }

  // Return a pointer to the RE2 instance matching |language|, or nullptr
  // if there is none.
  const RE2PlainPtr* FindMatcherFor(const std::string& language) const {
    const LanguageInfo* info = FindLanguageInfoFor(language);
    if (!info) {
      return nullptr;
    }
    size_t idx = info - kLanguageInfoMap;
    assert(idx < kLanguageInfoMapSize);
    return &re2s_[idx];
  }

 private:
  RE2PlainPtr re2s_[kLanguageInfoMapSize];
};

}  // namespace

// static
std::vector<const RE2PlainPtr*> PostBoxMatchers::GetMatchers(
    const Rule& country_rule) {
  static const StaticRE2Array kMatchers;

  // Always add any expressions defined for "und" (English-like defaults).
  std::vector<std::string> languages{"und"};
  for (const auto& language_tag : country_rule.GetLanguages()) {
    Language language(language_tag);
    languages.push_back(language.base);
  }

  std::vector<const RE2PlainPtr*> result;

  for (const auto& language_tag : languages) {
    const RE2PlainPtr* matcher = kMatchers.FindMatcherFor(language_tag);
    if (matcher != nullptr) {
      result.push_back(matcher);
    }
  }

  return result;
}

}  // namespace addressinput
}  // namespace i18n
