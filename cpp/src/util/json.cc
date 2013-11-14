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

#include "json.h"

#include <cassert>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/reader.h>

namespace i18n {
namespace addressinput {

Json::Json() : document_(new rapidjson::Document), valid_(false) {}

Json::~Json() {}

bool Json::ParseObject(const std::string& json) {
  document_->Parse<rapidjson::kParseValidateEncodingFlag>(json.c_str());
  valid_ = !document_->HasParseError() && document_->IsObject();
  return valid_;
}

bool Json::HasStringValueForKey(const std::string& key) const {
  assert(valid_);
  const rapidjson::Value::Member* member = document_->FindMember(key.c_str());
  return member != NULL && member->value.IsString();
}

std::string Json::GetStringValueForKey(const std::string& key) const {
  assert(valid_);
  const rapidjson::Value::Member* member = document_->FindMember(key.c_str());
  assert(member != NULL);
  assert(member->value.IsString());
  return std::string(member->value.GetString(),
                     member->value.GetStringLength());
}

}  // namespace addressinput
}  // namespace i18n
