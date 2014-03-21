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

#include "lookup_key.h"

#include <cassert>
#include <cstddef>
#include <map>
#include <string>
#include <utility>

#include <libaddressinput/address_data.h>
#include <libaddressinput/address_field.h>
#include <libaddressinput/util/basictypes.h>

namespace i18n {
namespace addressinput {

namespace {

const char kSlashDelim[] = "/";
const char kData[] = "data";
const char kUnknown[] = "ZZ";

}  // namespace

const AddressField LookupKey::kHierarchy[] = {
  COUNTRY,
  ADMIN_AREA,
  LOCALITY,
  DEPENDENT_LOCALITY
};

LookupKey::LookupKey() {
}

LookupKey::~LookupKey() {
}

void LookupKey::FromAddress(const AddressData& address) {
  nodes_.clear();

  if (address.region_code.empty()) {
    nodes_.insert(std::make_pair(COUNTRY, kUnknown));
  } else {
    for (size_t i = 0; i < arraysize(kHierarchy); ++i) {
      AddressField field = kHierarchy[i];
      const std::string& value = address.GetFieldValue(field);
      if (value.empty()) {
        break;
      }
      nodes_.insert(std::make_pair(field, value));
    }
  }
}

std::string LookupKey::ToKeyString(size_t max_depth) const {
  // TODO: For use by the address input widget, this key string would need to
  // also include a language tag to request data in the appropriate language.

  assert(max_depth < arraysize(kHierarchy));
  std::string key_string(kData);

  for (size_t i = 0; i <= max_depth; ++i) {
    AddressField field = kHierarchy[i];
    std::map<AddressField, std::string>::const_iterator it = nodes_.find(field);
    if (it == nodes_.end()) {
      break;
    }
    key_string.append(kSlashDelim);
    key_string.append(it->second);
  }

  return key_string;
}

const std::string& LookupKey::GetRegionCode() const {
  std::map<AddressField, std::string>::const_iterator it = nodes_.find(COUNTRY);
  assert(it != nodes_.end());
  return it->second;
}

size_t LookupKey::GetDepth() const {
  size_t depth = nodes_.size() - 1;
  assert(depth < arraysize(kHierarchy));
  return depth;
}

}  // namespace addressinput
}  // namespace i18n
