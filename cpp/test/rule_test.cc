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

#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "address_field_util.h"
#include "messages.h"
#include "region_data_constants.h"

namespace {

using i18n::addressinput::AddressField;
using i18n::addressinput::ADMIN_AREA;
using i18n::addressinput::LOCALITY;
using i18n::addressinput::NEWLINE;
using i18n::addressinput::ORGANIZATION;
using i18n::addressinput::POSTAL_CODE;
using i18n::addressinput::RECIPIENT;
using i18n::addressinput::RegionDataConstants;
using i18n::addressinput::Rule;
using i18n::addressinput::STREET_ADDRESS;

TEST(RuleTest, CopyOverwritesRule) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{"
                                       "\"fmt\":\"%S%Z\","
                                       "\"state_name_type\":\"area\","
                                       "\"zip_name_type\":\"postal\""
                                       "}"));

  Rule copy;
  EXPECT_NE(rule.GetFormat(), copy.GetFormat());
  EXPECT_NE(rule.GetAdminAreaNameMessageId(),
            copy.GetAdminAreaNameMessageId());
  EXPECT_NE(rule.GetPostalCodeNameMessageId(),
            copy.GetPostalCodeNameMessageId());

  copy.CopyFrom(rule);
  EXPECT_EQ(rule.GetFormat(), copy.GetFormat());
  EXPECT_EQ(rule.GetAdminAreaNameMessageId(),
            copy.GetAdminAreaNameMessageId());
  EXPECT_EQ(rule.GetPostalCodeNameMessageId(),
            copy.GetPostalCodeNameMessageId());
}

TEST(RuleTest, ParseOverwritesRule) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{"
                                       "\"fmt\":\"%S%Z\","
                                       "\"state_name_type\":\"area\","
                                       "\"zip_name_type\":\"postal\""
                                       "}"));
  EXPECT_FALSE(rule.GetFormat().empty());
  EXPECT_EQ(IDS_LIBADDRESSINPUT_I18N_AREA,
            rule.GetAdminAreaNameMessageId());
  EXPECT_EQ(IDS_LIBADDRESSINPUT_I18N_POSTAL_CODE_LABEL,
            rule.GetPostalCodeNameMessageId());

  ASSERT_TRUE(rule.ParseSerializedRule("{"
                                       "\"fmt\":\"\","
                                       "\"state_name_type\":\"do_si\","
                                       "\"zip_name_type\":\"zip\""
                                       "}"));
  EXPECT_TRUE(rule.GetFormat().empty());
  EXPECT_EQ(IDS_LIBADDRESSINPUT_I18N_DO_SI,
            rule.GetAdminAreaNameMessageId());
  EXPECT_EQ(IDS_LIBADDRESSINPUT_I18N_ZIP_CODE_LABEL,
            rule.GetPostalCodeNameMessageId());
}

TEST(RuleTest, ParsesFormatCorrectly) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{\"fmt\":\"%S\"}"));
  ASSERT_EQ(1, rule.GetFormat().size());
  EXPECT_EQ(ADMIN_AREA, rule.GetFormat()[0]);
}

TEST(RuleTest, EmptyStringIsNotValid) {
  Rule rule;
  EXPECT_FALSE(rule.ParseSerializedRule(std::string()));
}

TEST(RuleTest, EmptyDictionaryIsValid) {
  Rule rule;
  EXPECT_TRUE(rule.ParseSerializedRule("{}"));
}

// Tests for parsing the postal code name.
class PostalCodeNameParseTest
    : public testing::TestWithParam<std::pair<std::string, int> > {
 protected:
  Rule rule_;
};

// Verifies that a postal code name is parsed correctly.
TEST_P(PostalCodeNameParseTest, ParsedCorrectly) {
  ASSERT_TRUE(rule_.ParseSerializedRule(GetParam().first));
  EXPECT_EQ(GetParam().second, rule_.GetPostalCodeNameMessageId());
}

// Test parsing all postal code names.
INSTANTIATE_TEST_CASE_P(
    AllPostalCodeNames, PostalCodeNameParseTest,
    testing::Values(
        std::make_pair("{\"zip_name_type\":\"postal\"}",
                       IDS_LIBADDRESSINPUT_I18N_POSTAL_CODE_LABEL),
        std::make_pair("{\"zip_name_type\":\"zip\"}",
                       IDS_LIBADDRESSINPUT_I18N_ZIP_CODE_LABEL)));

// Tests for parsing the administrative area name.
class AdminAreaNameParseTest
    : public testing::TestWithParam<std::pair<std::string, int> > {
 protected:
  Rule rule_;
};

// Verifies that an administrative area name is parsed correctly.
TEST_P(AdminAreaNameParseTest, ParsedCorrectly) {
  ASSERT_TRUE(rule_.ParseSerializedRule(GetParam().first));
  EXPECT_EQ(GetParam().second, rule_.GetAdminAreaNameMessageId());
}

// Test parsing all administrative area names.
INSTANTIATE_TEST_CASE_P(
    AllAdminAreaNames, AdminAreaNameParseTest,
    testing::Values(
        std::make_pair("{\"state_name_type\":\"area\"}",
                       IDS_LIBADDRESSINPUT_I18N_AREA),
        std::make_pair("{\"state_name_type\":\"county\"}",
                       IDS_LIBADDRESSINPUT_I18N_COUNTY_LABEL),
        std::make_pair("{\"state_name_type\":\"department\"}",
                       IDS_LIBADDRESSINPUT_I18N_DEPARTMENT),
        std::make_pair("{\"state_name_type\":\"district\"}",
                       IDS_LIBADDRESSINPUT_I18N_DEPENDENT_LOCALITY_LABEL),
        std::make_pair("{\"state_name_type\":\"do_si\"}",
                       IDS_LIBADDRESSINPUT_I18N_DO_SI),
        std::make_pair("{\"state_name_type\":\"emirate\"}",
                       IDS_LIBADDRESSINPUT_I18N_EMIRATE),
        std::make_pair("{\"state_name_type\":\"island\"}",
                       IDS_LIBADDRESSINPUT_I18N_ISLAND),
        std::make_pair("{\"state_name_type\":\"parish\"}",
                       IDS_LIBADDRESSINPUT_I18N_PARISH),
        std::make_pair("{\"state_name_type\":\"prefecture\"}",
                       IDS_LIBADDRESSINPUT_I18N_PREFECTURE),
        std::make_pair("{\"state_name_type\":\"province\"}",
                       IDS_LIBADDRESSINPUT_I18N_PROVINCE),
        std::make_pair("{\"state_name_type\":\"state\"}",
                       IDS_LIBADDRESSINPUT_I18N_STATE_LABEL)));

// Tests for rule parsing.
class RuleParseTest : public testing::TestWithParam<std::string> {
 protected:
  Rule rule_;
};

// Verifies that a region data can be parsed successfully.
TEST_P(RuleParseTest, RegionDataParsedSuccessfully) {
  EXPECT_TRUE(rule_.ParseSerializedRule(
      RegionDataConstants::GetRegionData(GetParam())));
}

// Test parsing all region data.
INSTANTIATE_TEST_CASE_P(
    AllRulesTest, RuleParseTest,
    testing::ValuesIn(RegionDataConstants::GetRegionCodes()));

}  // namespace
