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

#include "address_field_util.h"

#include <libaddressinput/address_field.h>

#include <cassert>
#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace i18n {
namespace addressinput {

namespace {

std::map<char, AddressField> InitFields() {
  std::map<char, AddressField> fields;
  fields.insert(std::make_pair('R', COUNTRY));
  fields.insert(std::make_pair('S', ADMIN_AREA));
  fields.insert(std::make_pair('C', LOCALITY));
  fields.insert(std::make_pair('D', DEPENDENT_LOCALITY));
  fields.insert(std::make_pair('x', SORTING_CODE));
  fields.insert(std::make_pair('Z', POSTAL_CODE));
  fields.insert(std::make_pair('A', STREET_ADDRESS));
  fields.insert(std::make_pair('O', ORGANIZATION));
  fields.insert(std::make_pair('N', RECIPIENT));
  // An extension of AddressField enum used only internally:
  fields.insert(std::make_pair(
      'n', static_cast<AddressField>(NEWLINE)));
  return fields;
}

const std::map<char, AddressField>& GetFields() {
  static const std::map<char, AddressField> kFields(InitFields());
  return kFields;
}

bool IsTokenPrefix(char c) {
  return c == '%';
}

bool IsToken(char c) {
  return GetFields().find(c) != GetFields().end();
}

AddressField ParseToken(char c) {
  std::map<char, AddressField>::const_iterator it = GetFields().find(c);
  assert(it != GetFields().end());
  return it->second;
}

}  // namespace

void ParseAddressFieldsFormat(const std::string& format,
                              std::vector<AddressField>* fields) {
  assert(fields != NULL);
  fields->clear();
  for (std::string::const_iterator current = format.begin(),
                                   next = format.begin() + 1;
       current != format.end() && next != format.end();
       ++current, ++next) {
    if (IsTokenPrefix(*current) && IsToken(*next)) {
      fields->push_back(ParseToken(*next));
    }
  }
}

}  // namespace addressinput
}  // namespace i18n
