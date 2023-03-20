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
// See the License for the specific language governing permissions and
// limitations under the License.

#include "lookup_key.h"

#include <libaddressinput/address_data.h>

#include <cstddef>

#include <gtest/gtest.h>

#include "util/size.h"

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::LookupKey;

const size_t kMaxDepth = size(LookupKey::kHierarchy) - 1;

TEST(LookupKeyTest, Empty) {
  const AddressData address;
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/ZZ", lookup_key.ToKeyString(kMaxDepth));
}

TEST(LookupKeyTest, AddressDepth1) {
  const AddressData address{.region_code = "111"};
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ(0, lookup_key.GetDepth());
  EXPECT_EQ("data/111", lookup_key.ToKeyString(kMaxDepth));
}

TEST(LookupKeyTest, AddressDepth2) {
  const AddressData address{
      .region_code = "111",
      .administrative_area = "222",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ(1, lookup_key.GetDepth());
  EXPECT_EQ("data/111/222", lookup_key.ToKeyString(kMaxDepth));
}

TEST(LookupKeyTest, AddressDepth3) {
  const AddressData address{
      .region_code = "111",
      .administrative_area = "222",
      .locality = "333",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ(2, lookup_key.GetDepth());
  EXPECT_EQ("data/111/222/333", lookup_key.ToKeyString(kMaxDepth));
}

TEST(LookupKeyTest, AddressDepth4) {
  const AddressData address{
      .region_code = "111",
      .administrative_area = "222",
      .locality = "333",
      .dependent_locality = "444",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ(3, lookup_key.GetDepth());
  EXPECT_EQ("data/111/222/333/444", lookup_key.ToKeyString(kMaxDepth));
}

TEST(LookupKeyTest, AddressDepthNonContiguous) {
  const AddressData address{
      .region_code = "111",
      .administrative_area = "222",
      // No LOCALITY specified.
      .dependent_locality = "444",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ(1, lookup_key.GetDepth());
  EXPECT_EQ("data/111/222", lookup_key.ToKeyString(kMaxDepth));
}

TEST(LookupKeyTest, AddressDepthTerminateOnSlash) {
  const AddressData address{
      .region_code = "111",
      .administrative_area = "222",
      .locality = "3/3",  // No data should be requested for this LOCALITY.
      .dependent_locality = "444",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ(1, lookup_key.GetDepth());
  EXPECT_EQ("data/111/222", lookup_key.ToKeyString(kMaxDepth));
}

TEST(LookupKeyTest, RequestDepth) {
  const AddressData address{
      .region_code = "111",
      .administrative_area = "222",
      .locality = "333",
      .dependent_locality = "444",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/111", lookup_key.ToKeyString(0));
  EXPECT_EQ("data/111/222", lookup_key.ToKeyString(1));
  EXPECT_EQ("data/111/222/333", lookup_key.ToKeyString(2));
  EXPECT_EQ("data/111/222/333/444", lookup_key.ToKeyString(3));
}

TEST(LookupKeyTest, WithLanguageCodeDefaultLanguage) {
  // Use real data here as the choice of adding a language requires metadata.
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "ON",
      .language_code = "en",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/CA", lookup_key.ToKeyString(0));
  EXPECT_EQ("data/CA/ON", lookup_key.ToKeyString(1));
}

TEST(LookupKeyTest, WithLanguageCodeAlternateLanguage) {
  // Use real data here as the choice of adding a language requires metadata.
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "ON",
      .language_code = "fr",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/CA--fr", lookup_key.ToKeyString(0));
  EXPECT_EQ("data/CA/ON--fr", lookup_key.ToKeyString(1));
}

TEST(LookupKeyTest, WithLanguageCodeInvalidLanguage) {
  // Use real data here as the choice of adding a language requires metadata.
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "ON",
      .language_code = "de",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/CA", lookup_key.ToKeyString(0));
  EXPECT_EQ("data/CA/ON", lookup_key.ToKeyString(1));
}

TEST(LookupKeyTest, WithLanguageCodeAlternateLanguageNoState) {
  // Use real data here as the choice of adding a language requires metadata.
  // Afghanistan has multiple languages (including Pashto as an alternative)
  // but no subregions.
  const AddressData address{
      .region_code = "AF",
      .language_code = "ps",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/AF", lookup_key.ToKeyString(0));
}

TEST(LookupKeyTest, GetRegionCode) {
  const AddressData address{.region_code = "rrr"};
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ(address.region_code, lookup_key.GetRegionCode());
}

TEST(LookupKeyTest, FromAddressClearsExistingNodes) {
  AddressData address{
      .region_code = "111",
      .administrative_area = "222",
  };
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/111/222", lookup_key.ToKeyString(kMaxDepth));
  address.administrative_area.clear();
  lookup_key.FromAddress(address);
  EXPECT_EQ("data/111", lookup_key.ToKeyString(kMaxDepth));
}

}  // namespace
