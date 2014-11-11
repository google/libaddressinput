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

#include <cassert>
#include <cstddef>
#include <map>
#include <string>
#include <utility>

#include <re2/re2.h>

#include "address_field_util.h"
#include "format_element.h"
#include "grit.h"
#include "messages.h"
#include "region_data_constants.h"
#include "util/json.h"
#include "util/re2ptr.h"
#include "util/string_split.h"

namespace i18n {
namespace addressinput {

namespace {

typedef std::map<std::string, int> NameMessageIdMap;

// Used as a separator in a list of items. For example, the list of supported
// languages can be "de~fr~it".
const char kSeparator = '~';

NameMessageIdMap InitAdminAreaMessageIds() {
  NameMessageIdMap message_ids;
  message_ids.insert(std::make_pair(
      "area", IDS_LIBADDRESSINPUT_AREA));
  message_ids.insert(std::make_pair(
      "county", IDS_LIBADDRESSINPUT_COUNTY));
  message_ids.insert(std::make_pair(
      "department", IDS_LIBADDRESSINPUT_DEPARTMENT));
  message_ids.insert(std::make_pair(
      "district", IDS_LIBADDRESSINPUT_DISTRICT));
  message_ids.insert(std::make_pair(
      "do_si", IDS_LIBADDRESSINPUT_DO_SI));
  message_ids.insert(std::make_pair(
      "emirate", IDS_LIBADDRESSINPUT_EMIRATE));
  message_ids.insert(std::make_pair(
      "island", IDS_LIBADDRESSINPUT_ISLAND));
  message_ids.insert(std::make_pair(
      "oblast", IDS_LIBADDRESSINPUT_OBLAST));
  message_ids.insert(std::make_pair(
      "parish", IDS_LIBADDRESSINPUT_PARISH));
  message_ids.insert(std::make_pair(
      "prefecture", IDS_LIBADDRESSINPUT_PREFECTURE));
  message_ids.insert(std::make_pair(
      "province", IDS_LIBADDRESSINPUT_PROVINCE));
  message_ids.insert(std::make_pair(
      "state", IDS_LIBADDRESSINPUT_STATE));
  return message_ids;
}

const NameMessageIdMap& GetAdminAreaMessageIds() {
  static const NameMessageIdMap kAdminAreaMessageIds(InitAdminAreaMessageIds());
  return kAdminAreaMessageIds;
}

NameMessageIdMap InitPostalCodeMessageIds() {
  NameMessageIdMap message_ids;
  message_ids.insert(std::make_pair(
      "pin", IDS_LIBADDRESSINPUT_PIN_CODE_LABEL));
  message_ids.insert(std::make_pair(
      "postal", IDS_LIBADDRESSINPUT_POSTAL_CODE_LABEL));
  message_ids.insert(std::make_pair(
      "zip", IDS_LIBADDRESSINPUT_ZIP_CODE_LABEL));
  return message_ids;
}

const NameMessageIdMap& GetPostalCodeMessageIds() {
  static const NameMessageIdMap kPostalCodeMessageIds(
      InitPostalCodeMessageIds());
  return kPostalCodeMessageIds;
}

NameMessageIdMap InitLocalityMessageIds() {
  NameMessageIdMap message_ids;
  message_ids.insert(std::make_pair(
      "city", IDS_LIBADDRESSINPUT_LOCALITY_LABEL));
  message_ids.insert(std::make_pair(
      "post_town", IDS_LIBADDRESSINPUT_POST_TOWN));
  message_ids.insert(std::make_pair(
      "district", IDS_LIBADDRESSINPUT_DISTRICT));
  return message_ids;
}

const NameMessageIdMap& GetLocalityMessageIds() {
  static const NameMessageIdMap kLocalityMessageIds(
      InitLocalityMessageIds());
  return kLocalityMessageIds;
}

NameMessageIdMap InitSublocalityMessageIds() {
  NameMessageIdMap message_ids;
  message_ids.insert(std::make_pair(
      "suburb", IDS_LIBADDRESSINPUT_SUBURB));
  message_ids.insert(std::make_pair(
      "district", IDS_LIBADDRESSINPUT_DISTRICT));
  message_ids.insert(std::make_pair(
      "neighborhood", IDS_LIBADDRESSINPUT_NEIGHBORHOOD));
  message_ids.insert(std::make_pair(
      "village_township", IDS_LIBADDRESSINPUT_VILLAGE_TOWNSHIP));
  return message_ids;
}

const NameMessageIdMap& GetSublocalityMessageIds() {
  static const NameMessageIdMap kSublocalityMessageIds(
      InitSublocalityMessageIds());
  return kSublocalityMessageIds;
}

int GetMessageIdFromName(const std::string& name,
                         const NameMessageIdMap& message_ids) {
  NameMessageIdMap::const_iterator it = message_ids.find(name);
  return it != message_ids.end() ? it->second : INVALID_MESSAGE_ID;
}

// Determines whether a given string is a reg-exp or a string. We consider a
// string to be anything that doesn't contain characters with special meanings
// in regular expressions - (, [, \, {, ?. These special characters are all the
// ones that appear in the postal code regular expressions.
bool ContainsRegExSpecialCharacters(const std::string& input) {
  return input.find_first_of("([\\{?") != std::string::npos;
}

}  // namespace

Rule::Rule()
    : id_(),
      format_(),
      latin_format_(),
      required_(),
      sub_keys_(),
      languages_(),
      postal_code_matcher_(NULL),
      sole_postal_code_(),
      admin_area_name_message_id_(INVALID_MESSAGE_ID),
      postal_code_name_message_id_(INVALID_MESSAGE_ID),
      locality_name_message_id_(INVALID_MESSAGE_ID),
      sublocality_name_message_id_(INVALID_MESSAGE_ID),
      name_(),
      latin_name_(),
      postal_code_example_(),
      post_service_url_() {}

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
  assert(this != &rule);
  id_ = rule.id_;
  format_ = rule.format_;
  latin_format_ = rule.latin_format_;
  required_ = rule.required_;
  sub_keys_ = rule.sub_keys_;
  languages_ = rule.languages_;
  postal_code_matcher_.reset(
      rule.postal_code_matcher_ == NULL
          ? NULL
          : new RE2ptr(new RE2(rule.postal_code_matcher_->ptr->pattern(),
                               rule.postal_code_matcher_->ptr->options())));
  sole_postal_code_ = rule.sole_postal_code_;
  admin_area_name_message_id_ = rule.admin_area_name_message_id_;
  postal_code_name_message_id_ = rule.postal_code_name_message_id_;
  locality_name_message_id_ = rule.locality_name_message_id_;
  sublocality_name_message_id_ = rule.sublocality_name_message_id_;
  name_ = rule.name_;
  latin_name_ = rule.latin_name_;
  postal_code_example_ = rule.postal_code_example_;
  post_service_url_ = rule.post_service_url_;
}

bool Rule::ParseSerializedRule(const std::string& serialized_rule) {
  Json json;
  if (!json.ParseObject(serialized_rule)) {
    return false;
  }
  ParseJsonRule(json);
  return true;
}

void Rule::ParseJsonRule(const Json& json) {
  std::string value;
  if (json.GetStringValueForKey("id", &value)) {
    id_.swap(value);
  }

  if (json.GetStringValueForKey("fmt", &value)) {
    ParseFormatRule(value, &format_);
  }

  if (json.GetStringValueForKey("lfmt", &value)) {
    ParseFormatRule(value, &latin_format_);
  }

  if (json.GetStringValueForKey("require", &value)) {
    ParseAddressFieldsRequired(value, &required_);
  }

  if (json.GetStringValueForKey("sub_keys", &value)) {
    SplitString(value, kSeparator, &sub_keys_);
  }

  if (json.GetStringValueForKey("languages", &value)) {
    SplitString(value, kSeparator, &languages_);
  }

  sole_postal_code_.clear();
  if (json.GetStringValueForKey("zip", &value)) {
    // The "zip" field in the JSON data is used in two different ways to
    // validate the postal code. At the country level, the "zip" field indicates
    // a Java compatible regular expression corresponding to all postal codes in
    // the country. At other levels, the regular expression indicates the postal
    // code prefix expected for addresses in that region.
    //
    // In order to make the RE2 object created from the "zip" field useable for
    // both these purposes, the pattern string is here prefixed with "^" to
    // anchor it at the beginning of the string so that it can be used with
    // RE2::PartialMatch() to perform prefix matching or else with
    // RE2::FullMatch() to perform matching against the entire string.
    RE2::Options options;
    options.set_never_capture(true);
    RE2* matcher = new RE2("^(" + value + ")", options);
    if (matcher->ok()) {
      postal_code_matcher_.reset(new RE2ptr(matcher));
    } else {
      postal_code_matcher_.reset(NULL);
      delete matcher;
    }
    // If the "zip" field is not a regular expression, then it is the sole
    // postal code for this rule.
    if (!ContainsRegExSpecialCharacters(value)) {
      sole_postal_code_.swap(value);
    }
  }

  if (json.GetStringValueForKey("state_name_type", &value)) {
    admin_area_name_message_id_ =
        GetMessageIdFromName(value, GetAdminAreaMessageIds());
  }

  if (json.GetStringValueForKey("zip_name_type", &value)) {
    postal_code_name_message_id_ =
        GetMessageIdFromName(value, GetPostalCodeMessageIds());
  }

  if (json.GetStringValueForKey("locality_name_type", &value)) {
    locality_name_message_id_ =
        GetMessageIdFromName(value, GetLocalityMessageIds());
  }

  if (json.GetStringValueForKey("sublocality_name_type", &value)) {
    sublocality_name_message_id_ =
        GetMessageIdFromName(value, GetSublocalityMessageIds());
  }

  if (json.GetStringValueForKey("name", &value)) {
    name_.swap(value);
  }

  if (json.GetStringValueForKey("lname", &value)) {
    latin_name_.swap(value);
  }

  if (json.GetStringValueForKey("zipex", &value)) {
    postal_code_example_.swap(value);
  }

  if (json.GetStringValueForKey("posturl", &value)) {
    post_service_url_.swap(value);
  }
}

}  // namespace addressinput
}  // namespace i18n
