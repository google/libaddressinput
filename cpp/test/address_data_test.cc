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

#include <libaddressinput/address_data.h>

#include <libaddressinput/address_field.h>

#include <gtest/gtest.h>

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::AddressField;

using i18n::addressinput::COUNTRY;
using i18n::addressinput::ADMIN_AREA;
using i18n::addressinput::LOCALITY;
using i18n::addressinput::DEPENDENT_LOCALITY;
using i18n::addressinput::SORTING_CODE;
using i18n::addressinput::POSTAL_CODE;
using i18n::addressinput::STREET_ADDRESS;
using i18n::addressinput::RECIPIENT;

TEST(AddressDataTest, GetFieldValue) {
  AddressData address;
  address.region_code = "rrr";
  address.administrative_area = "sss";
  address.locality = "ccc";
  address.dependent_locality = "ddd";
  address.sorting_code = "xxx";
  address.postal_code = "zzz";
  address.recipient = "nnn";

  EXPECT_EQ(address.region_code,
            address.GetFieldValue(COUNTRY));
  EXPECT_EQ(address.administrative_area,
            address.GetFieldValue(ADMIN_AREA));
  EXPECT_EQ(address.locality,
            address.GetFieldValue(LOCALITY));
  EXPECT_EQ(address.dependent_locality,
            address.GetFieldValue(DEPENDENT_LOCALITY));
  EXPECT_EQ(address.sorting_code,
            address.GetFieldValue(SORTING_CODE));
  EXPECT_EQ(address.postal_code,
            address.GetFieldValue(POSTAL_CODE));
  EXPECT_EQ(address.recipient,
            address.GetFieldValue(RECIPIENT));
}

TEST(AddressDataTest, GetRepeatedFieldValue) {
  AddressData address;
  address.address_line.push_back("aaa");
  address.address_line.push_back("222");
  EXPECT_EQ(address.address_line,
            address.GetRepeatedFieldValue(STREET_ADDRESS));
}

TEST(AddressDataTest, IsFieldEmpty) {
  AddressData address;

  EXPECT_TRUE(address.IsFieldEmpty(COUNTRY));
  EXPECT_TRUE(address.IsFieldEmpty(ADMIN_AREA));
  EXPECT_TRUE(address.IsFieldEmpty(LOCALITY));
  EXPECT_TRUE(address.IsFieldEmpty(DEPENDENT_LOCALITY));
  EXPECT_TRUE(address.IsFieldEmpty(SORTING_CODE));
  EXPECT_TRUE(address.IsFieldEmpty(POSTAL_CODE));
  EXPECT_TRUE(address.IsFieldEmpty(STREET_ADDRESS));
  EXPECT_TRUE(address.IsFieldEmpty(RECIPIENT));

  address.region_code = "rrr";
  address.administrative_area = "sss";
  address.locality = "ccc";
  address.dependent_locality = "ddd";
  address.sorting_code = "xxx";
  address.postal_code = "zzz";
  address.address_line.push_back("aaa");
  address.recipient = "nnn";

  EXPECT_FALSE(address.IsFieldEmpty(COUNTRY));
  EXPECT_FALSE(address.IsFieldEmpty(ADMIN_AREA));
  EXPECT_FALSE(address.IsFieldEmpty(LOCALITY));
  EXPECT_FALSE(address.IsFieldEmpty(DEPENDENT_LOCALITY));
  EXPECT_FALSE(address.IsFieldEmpty(SORTING_CODE));
  EXPECT_FALSE(address.IsFieldEmpty(POSTAL_CODE));
  EXPECT_FALSE(address.IsFieldEmpty(STREET_ADDRESS));
  EXPECT_FALSE(address.IsFieldEmpty(RECIPIENT));
}

TEST(AddressDataTest, IsFieldEmptyVector) {
  AddressData address;
  EXPECT_TRUE(address.IsFieldEmpty(STREET_ADDRESS));
  address.address_line.push_back("");
  EXPECT_TRUE(address.IsFieldEmpty(STREET_ADDRESS));
  address.address_line.push_back("aaa");
  EXPECT_FALSE(address.IsFieldEmpty(STREET_ADDRESS));
  address.address_line.push_back("");
  EXPECT_FALSE(address.IsFieldEmpty(STREET_ADDRESS));
}

#ifndef NDEBUG

TEST(AddressDataTest, GetFieldValueInvalid) {
  AddressData address;
  ASSERT_DEATH(address.GetFieldValue(STREET_ADDRESS), "ssertion.*failed");
}

TEST(AddressDataTest, GetVectorFieldValueInvalid) {
  AddressData address;
  ASSERT_DEATH(address.GetRepeatedFieldValue(COUNTRY), "ssertion.*failed");
}

TEST(AddressDataTest, IsFieldEmptyInvalid) {
  static const AddressField invalid_field = static_cast<AddressField>(-1);
  AddressData address;
  ASSERT_DEATH(address.IsFieldEmpty(invalid_field), "ssertion.*failed");
}

#endif  // NDEBUG

}  // namespace
