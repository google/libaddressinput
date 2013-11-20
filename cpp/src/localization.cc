// Copyright (C) 2013 Google Inc.
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

#include <libaddressinput/localization.h>

#include <cassert>
#include <cstddef>
#include <string>

namespace i18n {
namespace addressinput {

namespace {

// For each language code XX with translations:
//    (1) Add a namespace XX here with an include of "XX_messages.cc".
//    (2) Add a wrapper that converts the char pointer to std::string. (GRIT
//        generated functions return char pointers.)
//    (2) Use the XX::GetStdString in the SetLanguage() method below.
namespace en {

#include "en_messages.cc"

std::string GetStdString(int message_id) {
  const char* str = GetString(message_id);
  return str != NULL ? std::string(str) : std::string();
}

}  // namespace en

}  // namespace

Localization::Localization() : get_string_(&en::GetStdString) {}

Localization::~Localization() {}

std::string Localization::GetString(int message_id) const {
  return get_string_(message_id);
}

void Localization::SetLanguage(const std::string& language_code) {
  if (language_code == "en") {
    get_string_ = &en::GetStdString;
  } else {
    assert(false);
  }
}

void Localization::SetGetter(std::string (*getter)(int)) {
  assert(getter != NULL);
  get_string_ = getter;
}

}  // namespace addressinput
}  // namespace i18n
