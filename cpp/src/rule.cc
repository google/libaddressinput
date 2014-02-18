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

#include "rule.h"

#include <libaddressinput/address_field.h>

#include <map>
#include <string>
#include <utility>

#include "address_field_util.h"
#include "grit.h"
#include "messages.h"
#include "region_data_constants.h"
#include "util/json.h"

namespace i18n {
namespace addressinput {

namespace {

typedef std::map<std::string, int> NameMessageIdMap;

const char kAdminAreaNameTypeKey[] = "state_name_type";
const char kFormatKey[] = "fmt";
const char kPostalCodeNameTypeKey[] = "zip_name_type";

NameMessageIdMap InitAdminAreaMessageIds() {
  NameMessageIdMap message_ids;
  message_ids.insert(std::make_pair(
      "area", IDS_LIBADDRESSINPUT_I18N_AREA));
  message_ids.insert(std::make_pair(
      "county", IDS_LIBADDRESSINPUT_I18N_COUNTY_LABEL));
  message_ids.insert(std::make_pair(
      "department", IDS_LIBADDRESSINPUT_I18N_DEPARTMENT));
  message_ids.insert(std::make_pair(
      "district", IDS_LIBADDRESSINPUT_I18N_DEPENDENT_LOCALITY_LABEL));
  message_ids.insert(std::make_pair(
      "do_si", IDS_LIBADDRESSINPUT_I18N_DO_SI));
  message_ids.insert(std::make_pair(
      "emirate", IDS_LIBADDRESSINPUT_I18N_EMIRATE));
  message_ids.insert(std::make_pair(
      "island", IDS_LIBADDRESSINPUT_I18N_ISLAND));
  message_ids.insert(std::make_pair(
      "parish", IDS_LIBADDRESSINPUT_I18N_PARISH));
  message_ids.insert(std::make_pair(
      "prefecture", IDS_LIBADDRESSINPUT_I18N_PREFECTURE));
  message_ids.insert(std::make_pair(
      "province", IDS_LIBADDRESSINPUT_I18N_PROVINCE));
  message_ids.insert(std::make_pair(
      "state", IDS_LIBADDRESSINPUT_I18N_STATE_LABEL));
  return message_ids;
}

const NameMessageIdMap& GetAdminAreaMessageIds() {
  static const NameMessageIdMap kAdminAreaMessageIds(InitAdminAreaMessageIds());
  return kAdminAreaMessageIds;
}

NameMessageIdMap InitPostalCodeMessageIds() {
  NameMessageIdMap message_ids;
  message_ids.insert(std::make_pair(
      "postal", IDS_LIBADDRESSINPUT_I18N_POSTAL_CODE_LABEL));
  message_ids.insert(std::make_pair(
      "zip", IDS_LIBADDRESSINPUT_I18N_ZIP_CODE_LABEL));
  return message_ids;
}

const NameMessageIdMap& GetPostalCodeMessageIds() {
  static const NameMessageIdMap kPostalCodeMessageIds(
      InitPostalCodeMessageIds());
  return kPostalCodeMessageIds;
}

int GetMessageIdFromName(const std::string& name,
                         const NameMessageIdMap& message_ids) {
  NameMessageIdMap::const_iterator it = message_ids.find(name);
  return it != message_ids.end() ? it->second : INVALID_MESSAGE_ID;
}

}  // namespace

Rule::Rule()
    : format_(),
      admin_area_name_message_id_(INVALID_MESSAGE_ID),
      postal_code_name_message_id_(INVALID_MESSAGE_ID) {}

Rule::~Rule() {}

// static
const Rule& Rule::GetDefault() {
  // Allocated once and leaked on shutdown.
  static Rule* default_rule = NULL;
  if (default_rule == NULL) {
    default_rule = new Rule;
    default_rule->ParseSerializedRule(
        RegionDataConstants::GetDefaultRegionData());
  }
  return *default_rule;
}

void Rule::CopyFrom(const Rule& rule) {
  format_ = rule.format_;
  admin_area_name_message_id_ = rule.admin_area_name_message_id_;
  postal_code_name_message_id_ = rule.postal_code_name_message_id_;
}

bool Rule::ParseSerializedRule(const std::string& serialized_rule) {
  Json json;
  if (!json.ParseObject(serialized_rule)) {
    return false;
  }

  if (json.HasStringValueForKey(kFormatKey)) {
    ParseAddressFieldsFormat(json.GetStringValueForKey(kFormatKey), &format_);
  }

  if (json.HasStringValueForKey(kAdminAreaNameTypeKey)) {
    admin_area_name_message_id_ =
        GetMessageIdFromName(json.GetStringValueForKey(kAdminAreaNameTypeKey),
                             GetAdminAreaMessageIds());
  }

  if (json.HasStringValueForKey(kPostalCodeNameTypeKey)) {
    postal_code_name_message_id_ =
        GetMessageIdFromName(json.GetStringValueForKey(kPostalCodeNameTypeKey),
                             GetPostalCodeMessageIds());
  }

  return true;
}

}  // namespace addressinput
}  // namespace i18n
