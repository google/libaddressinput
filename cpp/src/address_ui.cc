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

#include <cassert>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "address_field_util.h"
#include "grit.h"
#include "language.h"
#include "messages.h"
#include "region_data_constants.h"
#include "rule.h"

namespace i18n {
namespace addressinput {

namespace {

Language ChooseBestAddressLanguage(
    const std::vector<Language>& available_languages,
    bool has_latin_format,
    const Language& ui_language) {
  if (available_languages.empty()) {
    return ui_language;
  }

  if (ui_language.tag.empty()) {
    return available_languages.front();
  }

  // The conventionally formatted BCP 47 Latin script with a preceding subtag
  // separator.
  static const char kLatinScriptSuffix[] = "-Latn";
  Language latin_script_language(
      available_languages.front().base + kLatinScriptSuffix);
  if (has_latin_format && ui_language.has_latin_script) {
    return latin_script_language;
  }

  for (std::vector<Language>::const_iterator
       available_lang_it = available_languages.begin();
       available_lang_it != available_languages.end(); ++available_lang_it) {
    // Base language comparison works because no region supports the same base
    // language with different scripts, for now. For example, no region supports
    // "zh-Hant" and "zh-Hans" at the same time.
    if (ui_language.base == available_lang_it->base) {
      return *available_lang_it;
    }
  }

  return has_latin_format ? latin_script_language : available_languages.front();
}

std::string GetString(const Localization& localization,
                      AddressField field,
                      int admin_area_name_message_id,
                      int postal_code_name_message_id) {
  int messageId;
  switch (field) {
    case SORTING_CODE:
      // This needs no translation as it's used only in one locale.
      return "CEDEX";
    case COUNTRY:
      messageId = IDS_LIBADDRESSINPUT_COUNTRY_OR_REGION_LABEL;
      break;
    case ADMIN_AREA:
      messageId = admin_area_name_message_id;
      break;
    case LOCALITY:
      messageId = IDS_LIBADDRESSINPUT_LOCALITY_LABEL;
      break;
    case DEPENDENT_LOCALITY:
      messageId = IDS_LIBADDRESSINPUT_DISTRICT;
      break;
    case POSTAL_CODE:
      messageId = postal_code_name_message_id;
      break;
    case STREET_ADDRESS:
      messageId = IDS_LIBADDRESSINPUT_ADDRESS_LINE_1_LABEL;
      break;
    case RECIPIENT:
      messageId = IDS_LIBADDRESSINPUT_RECIPIENT_LABEL;
      break;
    default:
      messageId = INVALID_MESSAGE_ID;
  }
  return localization.GetString(messageId);
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
    const Localization& localization,
    std::string* best_address_language_tag) {
  assert(best_address_language_tag != NULL);
  std::vector<AddressUiComponent> result;

  Rule rule;
  rule.CopyFrom(Rule::GetDefault());
  if (!rule.ParseSerializedRule(
          RegionDataConstants::GetRegionData(region_code))) {
    return result;
  }

  std::vector<Language> available_languages;
  for (std::vector<std::string>::const_iterator language_tag_it =
       rule.GetLanguages().begin();
       language_tag_it != rule.GetLanguages().end(); ++language_tag_it) {
    available_languages.push_back(Language(*language_tag_it));
  }

  const Language& best_address_language = ChooseBestAddressLanguage(
      available_languages, !rule.GetLatinFormat().empty(),
      Language(localization.GetLanguage()));
  *best_address_language_tag = best_address_language.tag;

  const std::vector<AddressField>& format =
      !rule.GetLatinFormat().empty() &&
      best_address_language.has_latin_script
          ? rule.GetLatinFormat() : rule.GetFormat();

  // For avoiding showing an input field twice, when the field is displayed
  // twice on an envelope.
  std::set<AddressField> fields;

  bool previous_field_is_newline = true;
  bool next_field_is_newline = true;
  for (std::vector<AddressField>::const_iterator field_it = format.begin();
       field_it != format.end(); ++field_it) {
    if (IsNewline(*field_it)) {
      previous_field_is_newline = true;
      continue;
    }
    if (!fields.insert(*field_it).second) {
      continue;
    }
    AddressUiComponent component;
    std::vector<AddressField>::const_iterator next_field_it = field_it + 1;
    next_field_is_newline =
        next_field_it == format.end() || IsNewline(*next_field_it);
    component.length_hint = previous_field_is_newline && next_field_is_newline
                                ? AddressUiComponent::HINT_LONG
                                : AddressUiComponent::HINT_SHORT;
    previous_field_is_newline = false;
    component.field = *field_it;
    component.name = GetString(localization, *field_it,
        rule.GetAdminAreaNameMessageId(), rule.GetPostalCodeNameMessageId());
    result.push_back(component);
  }

  return result;
}

}  // namespace addressinput
}  // namespace i18n
