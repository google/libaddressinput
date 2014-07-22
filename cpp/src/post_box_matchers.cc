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

#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <re2/re2.h>

#include "language.h"
#include "rule.h"
#include "util/re2ptr.h"

namespace i18n {
namespace addressinput {

namespace {

std::map<std::string, const RE2ptr*> InitMatchers() {
  static const struct {
    const char* const language;
    const RE2ptr ptr;
  } kMatchers[] = {
    { "ar",
      /* "صندوق بريد|ص[-. ]ب" */
      new RE2("\xD8\xB5\xD9\x86\xD8\xAF\xD9\x88\xD9\x82 "
              "\xD8\xA8\xD8\xB1\xD9\x8A\xD8\xAF|\xD8\xB5[-. ]\xD8\xA8") },

    { "cs", new RE2("(?i)p\\.? ?p\\.? \\d") },
    { "da", new RE2("(?i)Postboks") },
    { "de", new RE2("(?i)Postfach") },

    { "el",
      /* "T\\.? ?Θ\\.? \\d{2}" */
      new RE2("(?i)T\\.? ?\xCE\x98\\.? \\d{2}") },

    { "en", new RE2("Private Bag|Post(?:al)? Box") },
    { "es", new RE2("(?i)(?:Apartado|Casillas) de correos?") },
    { "fi", new RE2("(?i)Postilokero|P\\.?L\\.? \\d") },
    { "hr", new RE2("(?i)p\\.? ?p\\.? \\d") },

    { "hu",
      /* "Postafi(?:[oó]|ó)k|Pf\\.? \\d" */
      new RE2("(?i)Postafi(?:[o\xC3\xB3]|o\xCC\x81)k|Pf\\.? \\d") },

    { "fr",
      /* "Bo(?:[iî]|î)te Postale|BP \\d|CEDEX \\d" */
      new RE2("(?i)Bo(?:[i\xC3\xAE]|i\xCC\x82)te Postale|BP \\d|CEDEX \\d") },

    { "ja",
      /* "私書箱\\d{1,5}号" */
      new RE2("(?i)\xE7\xA7\x81\xE6\x9B\xB8\xE7\xAE\xB1\\d{1,5}\xE5\x8F\xB7") },

    { "nl", new RE2("(?i)Postbus") },
    { "no", new RE2("(?i)Postboks") },
    { "pl", new RE2("(?i)Skr(?:\\.?|ytka) poczt(?:\\.?|owa)") },
    { "pt", new RE2("(?i)Apartado") },

    { "ru",
      /* "абонентский ящик|[аa]\\\" */
      new RE2("(?i)\xD0\xB0\xD0\xB1\xD0\xBE\xD0\xBD\xD0\xB5\xD0\xBD\xD1\x82\xD1"
              "\x81\xD0\xBA\xD0\xB8\xD0\xB9 \xD1\x8F\xD1\x89\xD0\xB8\xD0\xBA|"
              "[\xD0\xB0""a]\\\"\xD1\x8F (?:(?:\xE2\x84\x96|#|N) ?)?\\d") },

    { "sv", new RE2("(?i)Box \\d") },

    { "zh",
      /* "郵政信箱.{1,5}號|郵局第.{1,10}號信箱" */
      new RE2("(?i)\xE9\x83\xB5\xE6\x94\xBF\xE4\xBF\xA1\xE7\xAE\xB1.{1,5}"
              "\xE8\x99\x9F|\xE9\x83\xB5\xE5\xB1\x80\xE7\xAC\xAC.{1,10}"
              "\xE8\x99\x9F\xE4\xBF\xA1\xE7\xAE\xB1") },

    { "und", new RE2("P\\.? ?O\\.? Box") }
  };

  std::map<std::string, const RE2ptr*> matchers;

  for (size_t i = 0; i < sizeof kMatchers / sizeof *kMatchers; ++i) {
    matchers.insert(std::make_pair(kMatchers[i].language, &kMatchers[i].ptr));
  }

  return matchers;
}

}  // namespace

// static
std::vector<const RE2ptr*> PostBoxMatchers::GetMatchers(
    const Rule& country_rule) {
  static const std::map<std::string, const RE2ptr*> kMatchers(InitMatchers());

  // Always add any expressions defined for "und" (English-like defaults).
  std::vector<std::string> languages(1, "und");
  for (std::vector<std::string>::const_iterator
       it = country_rule.GetLanguages().begin();
       it != country_rule.GetLanguages().end(); ++it) {
    Language language(*it);
    languages.push_back(language.base);
  }

  std::vector<const RE2ptr*> result;

  for (std::vector<std::string>::const_iterator
       it = languages.begin();
       it != languages.end(); ++it) {
    std::map<std::string, const RE2ptr*>::const_iterator
        jt = kMatchers.find(*it);
    if (jt != kMatchers.end()) {
      result.push_back(jt->second);
    }
  }

  return result;
}

}  // namespace addressinput
}  // namespace i18n
