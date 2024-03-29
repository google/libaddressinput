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

TEST(AddressFormatterTest, GetStreetAddressLinesAsSingleLine_EmptyAddress) {
  const AddressData address;
  std::string result;
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_TRUE(result.empty());
}

TEST(AddressFormatterTest, GetStreetAddressLinesAsSingleLine_1Line) {
  AddressData address{
      .region_code = "US",  // Not used.
      .address_line{"Line 1"},
  };

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
  AddressData address{
      .region_code = "US",  // Not used.
      .address_line{
          "Line 1",
          "Line 2",
      },
  };

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
  EXPECT_EQ("Line 1، Line 2", result);
}

TEST(AddressFormatterTest, GetStreetAddressLinesAsSingleLine_5Lines) {
  const AddressData address{
      .region_code = "US",  // Not used.
      .address_line{
          "Line 1",
          "Line 2",
          "Line 3",
          "Line 4",
          "Line 5",
      },
      .language_code = "fr",
  };

  std::string result;
  GetStreetAddressLinesAsSingleLine(address, &result);
  EXPECT_EQ(result, "Line 1, Line 2, Line 3, Line 4, Line 5");
}

TEST(AddressFormatterTest, GetFormattedNationalAddressLocalLanguage) {
  AddressData address{
      .region_code = "NZ",
      .address_line{
          "Rotopapa",
          "Irwell 3RD",
      },
      .locality = "Leeston",
      .postal_code = "8704",
  };

  const std::vector<std::string> expected{
      "Rotopapa",
      "Irwell 3RD",
      "Leeston 8704",
  };

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
  static const char kTaiwanCity[] = "大安區";
  static const char kTaiwanAdmin[] = "台北市";
  static const char kTaiwanStreetLine[] = "台灣信義路三段33號";
  static const char kPostalCode[] = "106";

  const AddressData address{
      .region_code = "TW",
      .address_line{kTaiwanStreetLine},
      .administrative_area = kTaiwanAdmin,
      .locality = kTaiwanCity,
      .postal_code = kPostalCode,
      .language_code = "zh-Hant",
  };

  const std::vector<std::string> expected{
      kPostalCode,
      std::string(kTaiwanAdmin).append(kTaiwanCity),
      kTaiwanStreetLine,
  };

  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  std::string one_line;
  GetFormattedNationalAddressLine(address, &one_line);
  // No separators expected for Chinese.
  EXPECT_EQ(std::string(kPostalCode)
                .append(kTaiwanAdmin)
                .append(kTaiwanCity)
                .append(kTaiwanStreetLine),
            one_line);

  // Changing to the Latin variant will change the output.
  const AddressData latin_address{
      .region_code = "TW",
      .address_line{"No. 33, Section 3 Xinyi Rd"},
      .administrative_area = "Taipei City",
      .locality = "Da-an District",
      .postal_code = kPostalCode,
      .language_code = "zh-Latn",
  };

  const std::vector<std::string> expected_latin{
      "No. 33, Section 3 Xinyi Rd",
      "Da-an District, Taipei City 106",
  };

  lines.clear();
  GetFormattedNationalAddress(latin_address, &lines);
  EXPECT_EQ(expected_latin, lines);

  GetFormattedNationalAddressLine(latin_address, &one_line);
  // We expect ", " as the new-line replacements for zh-Latn.
  EXPECT_EQ("No. 33, Section 3 Xinyi Rd, Da-an District, Taipei City 106",
            one_line);
}

TEST(AddressFormatterTest, GetFormattedNationalAddressMultilingualCountry) {
  const AddressData address{
      .region_code = "CA",
      .address_line{
          "5 Rue du Tresor",
          "Apt. 4",
      },
      .administrative_area = "QC",
      .locality = "Montmagny",
      .postal_code = "G1R 123",
      .language_code = "fr",
  };

  const std::vector<std::string> expected{
      "5 Rue du Tresor",
      "Apt. 4",
      "Montmagny QC G1R 123",
  };

  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest, GetFormattedNationalAddress_InlineStreetAddress) {
  const AddressData address{
      .region_code = "CI",
      .address_line{"32 Boulevard Carde"},
      .locality = "Abidjan",
      .sorting_code = "64",
      .language_code = "zh-Hant",
  };

  const std::vector<std::string> expected{"64 32 Boulevard Carde Abidjan 64"};

  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest,
     GetFormattedNationalAddressMissingFields_LiteralsAroundField) {
  AddressData address{.region_code = "CH"};
  std::vector<std::string> expected;
  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.locality = "Zurich";
  expected.emplace_back("Zurich");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.postal_code = "8001";
  expected.back().assign("CH-8001 Zurich");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.locality.clear();
  expected.back().assign("CH-8001");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest,
     GetFormattedNationalAddressMissingFields_LiteralsBetweenFields) {
  AddressData address{.region_code = "US"};
  std::vector<std::string> expected;
  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.administrative_area = "CA";
  expected.emplace_back("CA");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.locality = "Los Angeles";
  expected.back().assign("Los Angeles, CA");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.postal_code = "90291";
  expected.back().assign("Los Angeles, CA 90291");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.administrative_area.clear();
  expected.back().assign("Los Angeles 90291");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.locality.clear();
  address.administrative_area = "CA";
  expected.back().assign("CA 90291");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest,
     GetFormattedNationalAddressMissingFields_LiteralOnSeparateLine) {
  AddressData address{.region_code = "AX"};
  std::vector<std::string> expected{"ÅLAND"};
  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.locality = "City";
  expected.emplace(expected.begin(), "City");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.postal_code = "123";
  expected.front().assign("AX-123 City");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest,
     GetFormattedNationalAddressMissingFields_LiteralBeforeField) {
  AddressData address{
      .region_code = "JP",
      .language_code = "ja",
  };
  std::vector<std::string> expected;
  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.postal_code = "123";
  expected.emplace_back("〒123");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.administrative_area = "Prefecture";
  expected.emplace_back("Prefecture");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.postal_code.clear();
  expected.erase(expected.begin());
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest,
     GetFormattedNationalAddress_LiteralBeforeOneAddressLine) {
  const AddressData address{
      .region_code = "JP",
      .address_line{"Roppongi Hills"},
      .administrative_area = "Tokyo",
      .language_code = "ja_Latn",
  };
  const std::vector<std::string> expected{"Roppongi Hills, Tokyo"};
  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest,
     GetFormattedNationalAddress_LiteralBeforeTwoAddressLines) {
  const AddressData address{
      .region_code = "JP",
      .address_line{
          "Roppongi Hills",
          "Mori Tower",
      },
      .administrative_area = "Tokyo",
      .language_code = "ja_Latn",
  };
  const std::vector<std::string> expected{
      "Roppongi Hills",
      "Mori Tower, Tokyo",
  };
  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

TEST(AddressFormatterTest,
     GetFormattedNationalAddressMissingFields_DuplicateField) {
  AddressData address{.region_code = "CI"};
  std::vector<std::string> expected;
  std::vector<std::string> lines;
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.sorting_code = "123";
  expected.emplace_back("123 123");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.address_line.emplace_back("456 Main St");
  expected.back().assign("123 456 Main St 123");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.locality = "Yamoussoukro";
  expected.back().assign("123 456 Main St Yamoussoukro 123");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.sorting_code.erase();
  expected.back().assign("456 Main St Yamoussoukro");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);

  address.address_line.clear();
  expected.back().assign("Yamoussoukro");
  GetFormattedNationalAddress(address, &lines);
  EXPECT_EQ(expected, lines);
}

}  // namespace
