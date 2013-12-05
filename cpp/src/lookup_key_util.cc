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

#include "lookup_key_util.h"

#include <cassert>
#include <string>

namespace i18n {
namespace addressinput {

LookupKeyUtil::LookupKeyUtil(const std::string& validation_data_url)
    : validation_data_url_(validation_data_url) {
  assert(validation_data_url_.length() > 0);
  assert(validation_data_url_[validation_data_url_.length() - 1] == '/');
}

LookupKeyUtil::~LookupKeyUtil() {}

std::string LookupKeyUtil::GetUrlForKey(const std::string& key) const {
  return validation_data_url_ + key;
}

std::string LookupKeyUtil::GetKeyForUrl(const std::string& url) const {
  return IsValidationDataUrl(url) ? url.substr(validation_data_url_.length())
                                  : std::string();
}

bool LookupKeyUtil::IsValidationDataUrl(const std::string& url) const {
  return
      url.compare(0, validation_data_url_.length(), validation_data_url_) == 0;
}

}  // namespace addressinput
}  // namespace i18n
