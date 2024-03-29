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

#include <libaddressinput/preload_supplier.h>

#include <libaddressinput/address_data.h>
#include <libaddressinput/callback.h>
#include <libaddressinput/null_storage.h>
#include <libaddressinput/supplier.h>

#include <cstddef>
#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "lookup_key.h"
#include "rule.h"
#include "testdata_source.h"

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::BuildCallback;
using i18n::addressinput::LookupKey;
using i18n::addressinput::NullStorage;
using i18n::addressinput::PreloadSupplier;
using i18n::addressinput::Rule;
using i18n::addressinput::Supplier;
using i18n::addressinput::TestdataSource;

class PreloadSupplierTest : public testing::Test {
 public:
  PreloadSupplierTest(const PreloadSupplierTest&) = delete;
  PreloadSupplierTest& operator=(const PreloadSupplierTest&) = delete;

 protected:
  PreloadSupplierTest()
      : supplier_(new TestdataSource(true), new NullStorage),
        loaded_callback_(BuildCallback(this, &PreloadSupplierTest::OnLoaded)),
        supplied_callback_(
            BuildCallback(this, &PreloadSupplierTest::OnSupplied)) {}

  PreloadSupplier supplier_;
  const std::unique_ptr<const PreloadSupplier::Callback> loaded_callback_;
  const std::unique_ptr<const Supplier::Callback> supplied_callback_;
  Supplier::RuleHierarchy hierarchy_;

 private:
  void OnLoaded(bool success, const std::string& region_code, int num_rules) {
    ASSERT_TRUE(success);
    ASSERT_FALSE(region_code.empty());
    ASSERT_LT(0, num_rules);
    ASSERT_TRUE(supplier_.IsLoaded(region_code));
  }

  void OnSupplied(bool success, const LookupKey& lookup_key,
                  const Supplier::RuleHierarchy& hierarchy) {
    ASSERT_TRUE(success);
    hierarchy_ = hierarchy;
  }
};

TEST_F(PreloadSupplierTest, GetUsRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey us_key;
  const AddressData us_address{.region_code = "US"};
  us_key.FromAddress(us_address);
  const Rule* rule = supplier_.GetRule(us_key);
  ASSERT_TRUE(rule != nullptr);
  EXPECT_EQ("data/US", rule->GetId());
}

TEST_F(PreloadSupplierTest, GetUsCaRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey ca_key;
  const AddressData ca_address{
      .region_code = "US",
      .administrative_area = "CA",
  };
  ca_key.FromAddress(ca_address);
  const Rule* rule = supplier_.GetRule(ca_key);
  ASSERT_TRUE(rule != nullptr);
  EXPECT_EQ("data/US/CA", rule->GetId());
}

TEST_F(PreloadSupplierTest, GetUsCaliforniaRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey ca_key;
  const AddressData ca_address{
      .region_code = "US",
      .administrative_area = "California",
  };
  ca_key.FromAddress(ca_address);
  const Rule* rule = supplier_.GetRule(ca_key);
  ASSERT_TRUE(rule != nullptr);
  EXPECT_EQ("data/US/CA", rule->GetId());
}

TEST_F(PreloadSupplierTest, GetZwRule) {
  supplier_.LoadRules("ZW", *loaded_callback_);
  LookupKey zw_key;
  const AddressData zw_address{.region_code = "ZW"};
  zw_key.FromAddress(zw_address);
  const Rule* rule = supplier_.GetRule(zw_key);
  ASSERT_TRUE(rule != nullptr);
  EXPECT_EQ("data/ZW", rule->GetId());
}

TEST_F(PreloadSupplierTest, GetUnknownRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey unknown_key;
  const AddressData unknown_address{
      .region_code = "US",
      .administrative_area = "ZZ",
  };
  unknown_key.FromAddress(unknown_address);
  const Rule* rule = supplier_.GetRule(unknown_key);
  EXPECT_TRUE(rule == nullptr);
}

TEST_F(PreloadSupplierTest, GetTooPreciseRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey precise_key;
  const AddressData precise_address{
      .region_code = "US",
      .administrative_area = "CA",
      .locality = "Mountain View",
  };
  precise_key.FromAddress(precise_address);
  const Rule* rule = supplier_.GetRule(precise_key);
  EXPECT_TRUE(rule == nullptr);
}

TEST_F(PreloadSupplierTest, GetRulesForRegion) {
  supplier_.LoadRules("CN", *loaded_callback_);
  const auto& rules = supplier_.GetRulesForRegion("CN");
  EXPECT_TRUE(rules.find("data/CN") != rules.end());
  EXPECT_LT(1U, rules.size());
}

TEST_F(PreloadSupplierTest, SupplyRegionCode) {
  supplier_.LoadRules("CA", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "NB",
  };
  key.FromAddress(address);

  supplier_.Supply(key, *supplied_callback_);

  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/CA/NB", hierarchy_.rule[1]->GetId());
  EXPECT_TRUE(hierarchy_.rule[2] == nullptr);  // No data on locality
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyGloballyRegionCode) {
  supplier_.LoadRules("CA", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "NB",
  };
  key.FromAddress(address);

  supplier_.SupplyGlobally(key, *supplied_callback_);

  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/CA/NB", hierarchy_.rule[1]->GetId());
  EXPECT_TRUE(hierarchy_.rule[2] == nullptr);  // No data on locality
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyRegionName) {
  supplier_.LoadRules("CA", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "New Brunswick",
  };
  key.FromAddress(address);

  supplier_.Supply(key, *supplied_callback_);

  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/CA/NB", hierarchy_.rule[1]->GetId());
  EXPECT_TRUE(hierarchy_.rule[2] == nullptr);  // No data on locality
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyGloballyRegionName) {
  supplier_.LoadRules("CA", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "New Brunswick",
  };
  key.FromAddress(address);

  supplier_.SupplyGlobally(key, *supplied_callback_);

  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/CA/NB", hierarchy_.rule[1]->GetId());
  EXPECT_TRUE(hierarchy_.rule[2] == nullptr);  // No data on locality
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyRegionNameLanguage) {
  supplier_.LoadRules("CA", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "Nouveau-Brunswick",
  };
  key.FromAddress(address);

  supplier_.Supply(key, *supplied_callback_);

  // If the language is not set, supply only looks for the region name in the
  // default language.
  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  EXPECT_TRUE(hierarchy_.rule[1] == nullptr);  // Admin Area not found.
  EXPECT_TRUE(hierarchy_.rule[2] == nullptr);  // No data on locality
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyRegionNameLanguageSet) {
  supplier_.LoadRules("CA", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "Nouveau-Brunswick",
      .language_code = "fr",
  };
  key.FromAddress(address);

  supplier_.Supply(key, *supplied_callback_);

  // If the language is set, supply will look for the names in that language.
  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/CA/NB--fr", hierarchy_.rule[1]->GetId());
  EXPECT_TRUE(hierarchy_.rule[2] == nullptr);  // No data on locality
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyGloballyRegionNameLanguage) {
  supplier_.LoadRules("CA", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CA",
      .administrative_area = "Nouveau-Brunswick",
  };
  key.FromAddress(address);

  supplier_.SupplyGlobally(key, *supplied_callback_);

  // SupplyGlobally looks for the region name in all available languages.
  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/CA/NB--fr", hierarchy_.rule[1]->GetId());
  EXPECT_TRUE(hierarchy_.rule[2] == nullptr);  // No data on locality
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyRegionNameHK) {
  supplier_.LoadRules("HK", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "HK",
      .administrative_area = "新界",
      .locality = "大嶼山石壁",
  };
  key.FromAddress(address);

  supplier_.Supply(key, *supplied_callback_);

  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/HK/新界", hierarchy_.rule[1]->GetId());
  ASSERT_TRUE(hierarchy_.rule[2] != nullptr);  // Locality
  EXPECT_EQ("data/HK/新界/大嶼山石壁", hierarchy_.rule[2]->GetId());
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyGloballyRegionNameHKEnglish) {
  supplier_.LoadRules("HK", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "HK",
      .administrative_area = "New Territories",
      .locality = "Tsing Yi",
  };
  key.FromAddress(address);

  supplier_.SupplyGlobally(key, *supplied_callback_);

  // SupplyGlobally looks for the region name in all available languages.
  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/HK/New Territories--en", hierarchy_.rule[1]->GetId());
  ASSERT_TRUE(hierarchy_.rule[2] != nullptr);  // Locality
  EXPECT_EQ("data/HK/New Territories/Tsing Yi--en",
            hierarchy_.rule[2]->GetId());
  EXPECT_TRUE(hierarchy_.rule[3] == nullptr);  // No data on sub-locality
}

TEST_F(PreloadSupplierTest, SupplyRegionNameAllLevels) {
  supplier_.LoadRules("CN", *loaded_callback_);
  LookupKey key;
  const AddressData address{
      .region_code = "CN",
      .administrative_area = "云南省",
      .locality = "临沧市",
      .dependent_locality = "临翔区",
  };
  key.FromAddress(address);

  supplier_.Supply(key, *supplied_callback_);

  ASSERT_TRUE(hierarchy_.rule[0] != nullptr);  // Country
  EXPECT_EQ(key.ToKeyString(0), hierarchy_.rule[0]->GetId());
  ASSERT_TRUE(hierarchy_.rule[1] != nullptr);  // Admin Area
  EXPECT_EQ("data/CN/云南省", hierarchy_.rule[1]->GetId());
  ASSERT_TRUE(hierarchy_.rule[2] != nullptr);  // Locality
  EXPECT_EQ("data/CN/云南省/临沧市", hierarchy_.rule[2]->GetId());
  ASSERT_TRUE(hierarchy_.rule[3] != nullptr);  // Sub-locality
  EXPECT_EQ("data/CN/云南省/临沧市/临翔区", hierarchy_.rule[3]->GetId());
}

TEST_F(PreloadSupplierTest, GetLoadedRuleDepth) {
  supplier_.LoadRules("CA", *loaded_callback_);
  EXPECT_EQ(2,
            supplier_.GetLoadedRuleDepth("data/CA"));  // country and admin area

  EXPECT_EQ(0, supplier_.GetLoadedRuleDepth(
                   "data/CN"));  // Rules not loaded for China.
  supplier_.LoadRules("CN", *loaded_callback_);
  EXPECT_EQ(4,
            supplier_.GetLoadedRuleDepth(
                "data/CN"));  // country, admin area, city, dependent locality.

  EXPECT_EQ(
      0, supplier_.GetLoadedRuleDepth("data/PP"));  // Not a valid region code.
}

}  // namespace
