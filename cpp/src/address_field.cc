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

#include <libaddressinput/address_field.h>

#include <ostream>

namespace i18n {
namespace addressinput {

std::ostream& operator<<(std::ostream& o, AddressField field) {
  switch (field) {
    case COUNTRY:
      o << "COUNTRY";
      break;
    case ADMIN_AREA:
      o << "ADMIN_AREA";
      break;
    case LOCALITY:
      o << "LOCALITY";
      break;
    case DEPENDENT_LOCALITY:
      o << "DEPENDENT_LOCALITY";
      break;
    case SORTING_CODE:
      o << "SORTING_CODE";
      break;
    case POSTAL_CODE:
      o << "POSTAL_CODE";
      break;
    case STREET_ADDRESS:
      o << "STREET_ADDRESS";
      break;
    case ORGANIZATION:
      o << "ORGANIZATION";
      break;
    case RECIPIENT:
      o << "RECIPIENT";
      break;
    default:
      o << "[INVALID]";
      break;
  }
  return o;
}

}  // namespace addressinput
}  // namespace i18n
