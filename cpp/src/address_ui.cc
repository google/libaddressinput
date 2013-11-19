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

#include <libaddressinput/address_ui.h>

#include <libaddressinput/address_field.h>
#include <libaddressinput/address_ui_component.h>
#include <libaddressinput/localization.h>

#include <string>
#include <vector>

#include "address_field_util.h"
#include "grit.h"
#include "messages.h"
#include "region_data_constants.h"
#include "rule.h"

namespace i18n {
namespace addressinput {

namespace {

// Parses the default region data into the static Rule object and returns a
// constant reference to this object. Cannot return a copy of the object,
// because Rule objects are not copyable.
const Rule& InitDefaultRule() {
  static Rule rule;
  rule.ParseSerializedRule(RegionDataConstants::GetDefaultRegionData());
  return rule;
}

// Returns the constant reference to the Rule object from InitDefaultRule(). The
// static object is in InitDefaultRule(), but this function maintains a constant
// static reference to it. The constant static reference avoids re-parsing the
// default region data.
const Rule& GetDefaultRule() {
  static const Rule& kDefaultRule(InitDefaultRule());
  return kDefaultRule;
}

int GetMessageIdForField(AddressField field,
                         int admin_area_name_message_id,
                         int postal_code_name_message_id) {
  switch (field) {
    case COUNTRY:
      return IDS_LIBADDRESSINPUT_I18N_COUNTRY_LABEL;
    case ADMIN_AREA:
      return admin_area_name_message_id;
    case LOCALITY:
      return IDS_LIBADDRESSINPUT_I18N_LOCALITY_LABEL;
    case DEPENDENT_LOCALITY:
      return IDS_LIBADDRESSINPUT_I18N_DEPENDENT_LOCALITY_LABEL;
    case SORTING_CODE:
      return IDS_LIBADDRESSINPUT_I18N_CEDEX_LABEL;
    case POSTAL_CODE:
      return postal_code_name_message_id;
    case STREET_ADDRESS:
      return IDS_LIBADDRESSINPUT_I18N_ADDRESS_LINE1_LABEL;
    case ORGANIZATION:
      return IDS_LIBADDRESSINPUT_I18N_ORGANIZATION_LABEL;
    case RECIPIENT:
      return IDS_LIBADDRESSINPUT_I18N_RECIPIENT_LABEL;
    default:
      return INVALID_MESSAGE_ID;
  }
}

bool IsNewline(AddressField field) {
  // NEWLINE is an extension for AddressField enum that's used only internally.
  return field == static_cast<AddressField>(NEWLINE);
}

}  // namespace

const std::vector<std::string>& GetRegionCodes() {
  return RegionDataConstants::GetRegionCodes();
}

std::vector<AddressUiComponent> BuildComponents(
    const std::string& region_code,
    const Localization& localization) {
  std::vector<AddressUiComponent> result;

  Rule rule;
  rule.CopyFrom(GetDefaultRule());
  if (!rule.ParseSerializedRule(
           RegionDataConstants::GetRegionData(region_code))) {
    return result;
  }

  bool previous_field_is_newline = true;
  bool next_field_is_newline = true;
  for (std::vector<AddressField>::const_iterator field_it =
       rule.GetFormat().begin();
       field_it != rule.GetFormat().end(); ++field_it) {
    if (IsNewline(*field_it)) {
      previous_field_is_newline = true;
      continue;
    }
    AddressUiComponent component;
    std::vector<AddressField>::const_iterator next_field_it = field_it + 1;
    next_field_is_newline =
        next_field_it == rule.GetFormat().end() || IsNewline(*next_field_it);
    component.length_hint = previous_field_is_newline && next_field_is_newline
                                ? AddressUiComponent::HINT_LONG
                                : AddressUiComponent::HINT_SHORT;
    previous_field_is_newline = false;
    component.field = *field_it;
    component.name = localization.GetString(
        GetMessageIdForField(*field_it, rule.GetAdminAreaNameMessageId(),
                             rule.GetPostalCodeNameMessageId()));
    result.push_back(component);
  }

  return result;
}

}  // namespace addressinput
}  // namespace i18n
