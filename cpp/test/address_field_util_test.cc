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

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "format_element.h"

namespace {

using i18n::addressinput::AddressField;
using i18n::addressinput::FormatElement;
using i18n::addressinput::ParseFormatRule;

using i18n::addressinput::COUNTRY;
using i18n::addressinput::LOCALITY;
using i18n::addressinput::POSTAL_CODE;
using i18n::addressinput::STREET_ADDRESS;
using i18n::addressinput::ORGANIZATION;
using i18n::addressinput::RECIPIENT;

TEST(AddressFieldUtilTest, FormatParseNewline) {
  std::vector<FormatElement> actual;
  ParseFormatRule("%O%n%N%n%A%nAX-%Z %C%nÅLAND", &actual);

  const std::vector<FormatElement> expected{
      FormatElement{ORGANIZATION},
      FormatElement{},
      FormatElement{RECIPIENT},
      FormatElement{},
      FormatElement{STREET_ADDRESS},
      FormatElement{},
      FormatElement{"AX-"},
      FormatElement{POSTAL_CODE},
      FormatElement{" "},
      FormatElement{LOCALITY},
      FormatElement{},
      FormatElement{"ÅLAND"},
  };

  EXPECT_EQ(expected, actual);
}

TEST(AddressFieldUtilTest, FormatUnknownTokenIsIgnored) {
  std::vector<FormatElement> actual;
  ParseFormatRule("%1%R", &actual);  // %1 is not supported.
  const std::vector<FormatElement> expected{FormatElement{COUNTRY}};
  EXPECT_EQ(expected, actual);
}

TEST(AddressFieldUtilTest, FormatPrefixWithoutTokenIsIgnored) {
  std::vector<FormatElement> actual;
  ParseFormatRule("%", &actual);
  EXPECT_TRUE(actual.empty());
}

TEST(AddressFieldUtilTest, FormatEmptyString) {
  std::vector<FormatElement> fields;
  ParseFormatRule(std::string(), &fields);
  EXPECT_TRUE(fields.empty());
}

TEST(AddressFieldUtilTest, RequiredParseDefault) {
  std::vector<AddressField> actual;
  ParseAddressFieldsRequired("AC", &actual);

  const std::vector<AddressField> expected{
      STREET_ADDRESS,
      LOCALITY,
  };

  EXPECT_EQ(expected, actual);
}

TEST(AddressFieldUtilTest, RequiredEmptyString) {
  std::vector<AddressField> fields;
  ParseAddressFieldsRequired(std::string(), &fields);
  EXPECT_TRUE(fields.empty());
}

}  // namespace
