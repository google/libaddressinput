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

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "format_element.h"

namespace i18n {
namespace addressinput {

namespace {

std::map<char, AddressField> InitFields() {
  std::map<char, AddressField> fields;
  fields.insert(std::make_pair('R', COUNTRY));
  fields.insert(std::make_pair('S', ADMIN_AREA));
  fields.insert(std::make_pair('C', LOCALITY));
  fields.insert(std::make_pair('D', DEPENDENT_LOCALITY));
  fields.insert(std::make_pair('X', SORTING_CODE));
  fields.insert(std::make_pair('Z', POSTAL_CODE));
  fields.insert(std::make_pair('A', STREET_ADDRESS));
  fields.insert(std::make_pair('O', ORGANIZATION));
  fields.insert(std::make_pair('N', RECIPIENT));
  return fields;
}

const std::map<char, AddressField>& GetFields() {
  static const std::map<char, AddressField> kFields(InitFields());
  return kFields;
}

bool IsFieldToken(char c) {
  return GetFields().find(c) != GetFields().end();
}

AddressField ParseFieldToken(char c) {
  std::map<char, AddressField>::const_iterator it = GetFields().find(c);
  assert(it != GetFields().end());
  return it->second;
}

}  // namespace

void ParseFormatRule(const std::string& format,
                     std::vector<FormatElement>* elements) {
  assert(elements != NULL);
  elements->clear();

  std::string::const_iterator prev = format.begin();
  for (std::string::const_iterator next = format.begin();
       next != format.end(); prev = ++next) {
    // Find the next field element or newline (indicated by %<TOKEN>).
    if ((next = std::find(next, format.end(), '%')) == format.end()) {
      // No more tokens in the format string.
      break;
    }
    if (prev < next) {
      // Push back preceding literal.
      elements->push_back(FormatElement(std::string(prev, next)));
    }
    if ((prev = ++next) == format.end()) {
      // Move forward and check we haven't reached the end of the string
      // (unlikely, it shouldn't end with %).
      break;
    }
    // Process the token after the %.
    if (*next == 'n') {
      elements->push_back(FormatElement());
    } else if (IsFieldToken(*next)) {
      elements->push_back(FormatElement(ParseFieldToken(*next)));
    }  // Else it's an unknown token, we ignore it.
  }
  // Push back any trailing literal.
  if (prev != format.end()) {
    elements->push_back(FormatElement(std::string(prev, format.end())));
  }
}

void ParseAddressFieldsRequired(const std::string& required,
                                std::vector<AddressField>* fields) {
  assert(fields != NULL);
  fields->clear();
  for (std::string::const_iterator it = required.begin();
       it != required.end(); ++it) {
    if (IsFieldToken(*it)) {
      fields->push_back(ParseFieldToken(*it));
    }
  }
}

}  // namespace addressinput
}  // namespace i18n
