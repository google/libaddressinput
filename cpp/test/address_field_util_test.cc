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

namespace {

using i18n::addressinput::AddressField;
using i18n::addressinput::COUNTRY;
using i18n::addressinput::LOCALITY;
using i18n::addressinput::NEWLINE;
using i18n::addressinput::ParseAddressFieldsFormat;
using i18n::addressinput::POSTAL_CODE;
using i18n::addressinput::RECIPIENT;
using i18n::addressinput::STREET_ADDRESS;

TEST(AddressFieldUtilTest, FormatParseNewline) {
  std::vector<AddressField> actual;
  ParseAddressFieldsFormat("%O%n%N%n%A%nAX-%Z %C%nÅLAND", &actual);

  std::vector<AddressField> expected;
  expected.push_back(static_cast<AddressField>(NEWLINE));
  expected.push_back(RECIPIENT);
  expected.push_back(static_cast<AddressField>(NEWLINE));
  expected.push_back(STREET_ADDRESS);
  expected.push_back(static_cast<AddressField>(NEWLINE));
  expected.push_back(POSTAL_CODE);
  expected.push_back(LOCALITY);
  expected.push_back(static_cast<AddressField>(NEWLINE));

  EXPECT_EQ(expected, actual);
}

TEST(AddressFieldUtilTest, FormatDoubleTokenPrefixIsIgnored) {
  std::vector<AddressField> actual;
  ParseAddressFieldsFormat("%%R", &actual);
  std::vector<AddressField> expected(1, COUNTRY);
  EXPECT_EQ(expected, actual);
}

TEST(AddressFieldUtilTest, FormatPrefixWithoutTokenIsIgnored) {
  std::vector<AddressField> actual;
  ParseAddressFieldsFormat("%", &actual);
  EXPECT_TRUE(actual.empty());
}

TEST(AddressFieldUtilTest, FormatEmptyString) {
  std::vector<AddressField> fields;
  ParseAddressFieldsFormat(std::string(), &fields);
  EXPECT_TRUE(fields.empty());
}

TEST(AddressFieldUtilTest, RequiredParseDefault) {
  std::vector<AddressField> actual;
  ParseAddressFieldsRequired("AC", &actual);

  std::vector<AddressField> expected;
  expected.push_back(STREET_ADDRESS);
  expected.push_back(LOCALITY);

  EXPECT_EQ(expected, actual);
}

TEST(AddressFieldUtilTest, RequiredEmptyString) {
  std::vector<AddressField> fields;
  ParseAddressFieldsRequired(std::string(), &fields);
  EXPECT_TRUE(fields.empty());
}

}  // namespace
