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
#include <string>

#include "messages.h"

namespace i18n {
namespace addressinput {

namespace {

#include "en_messages.cc"

std::string GetEnglishString(int message_id) {
  const char* str = GetString(message_id);
  return str != nullptr ? std::string(str) : std::string();
}

}  // namespace

Localization::Localization() : get_string_(&GetEnglishString) {}

std::string Localization::GetString(int message_id) const {
  return get_string_(message_id);
}

void Localization::SetGetter(std::string (*getter)(int)) {
  assert(getter != nullptr);
  get_string_ = getter;
}

}  // namespace addressinput
}  // namespace i18n
