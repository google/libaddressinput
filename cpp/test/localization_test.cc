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

#include <libaddressinput/localization.h>

#include <string>

#include <gtest/gtest.h>

#include "grit.h"
#include "messages.h"

namespace {

using i18n::addressinput::INVALID_MESSAGE_ID;
using i18n::addressinput::Localization;

// Tests for Localization object.
class LocalizationTest : public testing::TestWithParam<int> {
 public:
  LocalizationTest(const LocalizationTest&) = delete;
  LocalizationTest& operator=(const LocalizationTest&) = delete;

 protected:
  LocalizationTest() = default;
  Localization localization_;
};

// Verifies that a custom message getter can be used.
const char kValidMessage[] = "Data";
std::string GetValidMessage(int message_id) { return kValidMessage; }
TEST_P(LocalizationTest, ValidStringGetterCanBeUsed) {
  localization_.SetGetter(&GetValidMessage);
  EXPECT_EQ(kValidMessage, localization_.GetString(GetParam()));
}

// Verifies that the default language for messages does not have empty strings.
TEST_P(LocalizationTest, DefaultStringIsNotEmpty) {
  EXPECT_FALSE(localization_.GetString(GetParam()).empty());
}

// Verifies that the messages do not have newlines.
TEST_P(LocalizationTest, NoNewline) {
  EXPECT_EQ(std::string::npos, localization_.GetString(GetParam()).find('\n'));
}

// Verifies that the messages do not have double spaces.
TEST_P(LocalizationTest, NoDoubleSpace) {
  EXPECT_EQ(std::string::npos,
            localization_.GetString(GetParam()).find(std::string(2U, ' ')));
}

// Tests all message identifiers.
INSTANTIATE_TEST_SUITE_P(
    AllMessages, LocalizationTest,
    testing::Values(
        IDS_LIBADDRESSINPUT_COUNTRY_OR_REGION_LABEL,
        IDS_LIBADDRESSINPUT_LOCALITY_LABEL,
        IDS_LIBADDRESSINPUT_ADDRESS_LINE_1_LABEL,
        IDS_LIBADDRESSINPUT_PIN_CODE_LABEL,
        IDS_LIBADDRESSINPUT_POSTAL_CODE_LABEL,
        IDS_LIBADDRESSINPUT_ZIP_CODE_LABEL, IDS_LIBADDRESSINPUT_AREA,
        IDS_LIBADDRESSINPUT_COUNTY, IDS_LIBADDRESSINPUT_DEPARTMENT,
        IDS_LIBADDRESSINPUT_DISTRICT, IDS_LIBADDRESSINPUT_DO_SI,
        IDS_LIBADDRESSINPUT_EMIRATE, IDS_LIBADDRESSINPUT_ISLAND,
        IDS_LIBADDRESSINPUT_PARISH, IDS_LIBADDRESSINPUT_PREFECTURE,
        IDS_LIBADDRESSINPUT_PROVINCE, IDS_LIBADDRESSINPUT_STATE,
        IDS_LIBADDRESSINPUT_ORGANIZATION_LABEL,
        IDS_LIBADDRESSINPUT_RECIPIENT_LABEL));

// Verifies that an invalid message identifier results in an empty string in the
// default configuration.
TEST_F(LocalizationTest, InvalidMessageIsEmptyString) {
  EXPECT_TRUE(localization_.GetString(INVALID_MESSAGE_ID).empty());
}

}  // namespace
