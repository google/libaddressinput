// Copyright (C) 2014 Google Inc.
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
// See the License for the specific language_code governing permissions and
// limitations under the License.

#include <libaddressinput/address_formatter.h>

#include <libaddressinput/address_data.h>

#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::GetFormattedNationalAddress;
using i18n::addressinput::GetFormattedNationalAddressLine;
using i18n::addressinput::GetStreetAddressLinesAsSingleLine;

TEST(AddressFormatterTest, GetStreetAddressLinesAsSingleLine_1Line) {
  AddressData address;
  address.region_code = "US";  // Not used.
  address.address_line.push_back("Line 1");

  std::string result;
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ("Line 1", result);

  // Setting the language_code, with one line, shouldn't affect anything.
  address.language_code = "en";
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ("Line 1", result);

  address.language_code = "zh-Hans";
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ("Line 1", result);
}

TEST(AddressFormatterTest, GetStreetAddressLinesAsSingleLine_2Lines) {
  AddressData address;
  address.region_code = "US";  // Not used.
  address.address_line.push_back("Line 1");
  address.address_line.push_back("Line 2");

  std::string result;
  GetStreetAddressLinesAsSingleLine(address, &result);
  // Default separator if no language_code specified: ", "
  EXPECT_EQ("Line 1, Line 2", result);

  address.language_code = "en";
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ("Line 1, Line 2", result);

  address.language_code = "zh-Hans";
  GetStreetAddressLinesAsSingleLine(address, &result);
  // Chinese has no separator.
  EXPECT_EQ("Line 1Line 2", result);

  address.language_code = "ko";
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ("Line 1 Line 2", result);

  address.language_code = "ar";
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ("Line 1\xD8\x8C" " Line 2", result);  // Arabic comma.
}

TEST(AddressFormatterTest, GetStreetAddressLinesAsSingleLine_5Lines) {
  AddressData address;
  address.region_code = "US";  // Not used.
  address.address_line.push_back("Line 1");
  address.address_line.push_back("Line 2");
  address.address_line.push_back("Line 3");
  address.address_line.push_back("Line 4");
  address.address_line.push_back("Line 5");
  address.language_code = "fr";

  std::string result;
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ(result, "Line 1, Line 2, Line 3, Line 4, Line 5");
}

TEST(AddressFormatterTest, GetFormattedNationalAddressLocalLanguage) {
  AddressData address;
  address.region_code = "NZ";
  address.address_line.push_back("Rotopapa");
  address.address_line.push_back("Irwell 3RD");
  address.postal_code = "8704";
  address.locality = "Leeston";

  std::vector<std::string> expected;
  expected.push_back("Rotopapa");
  expected.push_back("Irwell 3RD");
  expected.push_back("Leeston 8704");

  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  // Should be the same result no matter what the language_code is. We choose an
  // unlikely language_code code to illustrate this.
  address.language_code = "en-Latn-CN";

  lines.clear();
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  std::string one_line;
  GetFormattedNationalAddressLine(address, &one_line);
  EXPECT_EQ("Rotopapa, Irwell 3RD, Leeston 8704", one_line);
}

TEST(AddressFormatterTest, GetFormattedNationalAddressLatinFormat) {
  /* 大安區 */
  static const char kTaiwanCity[] = "\xE5\xA4\xA7\xE5\xAE\x89\xE5\x8D\x80";
  /* 台北市 */
  static const char kTaiwanAdmin[] = "\xE5\x8F\xB0\xE5\x8C\x97\xE5\xB8\x82";
  /* 台灣信義路三段33號 */
  static const char kTaiwanStreetLine[]= "\xE5\x8F\xB0\xE7\x81\xA3\xE4\xBF\xA1"
    "\xE7\xBE\xA9\xE8\xB7\xAF\xE4\xB8\x89\xE6\xAE\xB5" "33" "\xE8\x99\x9F";
  static const char kPostalCode[] = "106";

  AddressData address;
  address.region_code = "TW";
  address.address_line.push_back(kTaiwanStreetLine);
  address.postal_code = kPostalCode;
  address.locality = kTaiwanCity;
  address.administrative_area = kTaiwanAdmin;
  address.language_code = "zh-Hant";

  std::vector<std::string> expected;
  expected.push_back(kPostalCode);
  expected.push_back(std::string(kTaiwanAdmin).append(kTaiwanCity));
  expected.push_back(kTaiwanStreetLine);

  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  std::string one_line;
  GetFormattedNationalAddressLine(address, &one_line);
  // No separators expected for Chinese.
  EXPECT_EQ(std::string(kPostalCode).append(kTaiwanAdmin).append(kTaiwanCity)
            .append(kTaiwanStreetLine),
            one_line);

  // Changing to the latin variant will change the output.
  AddressData latin_address;
  latin_address.region_code = "TW";
  latin_address.address_line.push_back("No. 33, Section 3 Xinyi Rd");
  latin_address.postal_code = kPostalCode;
  latin_address.locality = "Da-an District";
  latin_address.administrative_area = "Taipei City";
  latin_address.language_code = "zh-Latn";

  std::vector<std::string> expected_latin;
  expected_latin.push_back("No. 33, Section 3 Xinyi Rd");
  expected_latin.push_back("Da-an District, Taipei City 106");

  lines.clear();
  GetFormattedNationalAddress(latin_address, &lines);
  EXPECT_EQ(expected_latin, lines);

  GetFormattedNationalAddressLine(latin_address, &one_line);
  // We expect ", " as the new-line replacements for zh-Latn.
  EXPECT_EQ("No. 33, Section 3 Xinyi Rd, Da-an District, Taipei City 106",
            one_line);
}

TEST(AddressFormatterTest, GetFormattedNationalAddressMultilingualCountry) {
  AddressData address;
  address.region_code = "CA";
  address.address_line.push_back("5 Rue du Tresor");
  address.address_line.push_back("Apt. 4");
  address.administrative_area = "QC";
  address.postal_code = "G1R 123";
  address.locality = "Montmagny";
  address.language_code = "fr";

  std::vector<std::string> expected;
  expected.push_back("5 Rue du Tresor");
  expected.push_back("Apt. 4");
  expected.push_back("Montmagny QC G1R 123");

  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

}  // namespace
