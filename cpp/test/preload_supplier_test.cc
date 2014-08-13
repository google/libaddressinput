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
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <cstddef>
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
using i18n::addressinput::scoped_ptr;
using i18n::addressinput::TestdataSource;

class PreloadSupplierTest : public testing::Test {
 protected:
  PreloadSupplierTest()
      : supplier_(new TestdataSource(true), new NullStorage),
        loaded_callback_(BuildCallback(this, &PreloadSupplierTest::OnLoaded)) {}

  PreloadSupplier supplier_;
  const scoped_ptr<const PreloadSupplier::Callback> loaded_callback_;

 private:
  void OnLoaded(bool success, const std::string& region_code, int num_rules) {
    ASSERT_TRUE(success);
    ASSERT_FALSE(region_code.empty());
    ASSERT_LT(0, num_rules);
    ASSERT_TRUE(supplier_.IsLoaded(region_code));
  }

  DISALLOW_COPY_AND_ASSIGN(PreloadSupplierTest);
};

TEST_F(PreloadSupplierTest, GetUsRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey us_key;
  AddressData us_address;
  us_address.region_code = "US";
  us_key.FromAddress(us_address);
  const Rule* rule = supplier_.GetRule(us_key);
  ASSERT_TRUE(rule != NULL);
  EXPECT_EQ("data/US", rule->GetId());
}

TEST_F(PreloadSupplierTest, GetUsCaRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey ca_key;
  AddressData ca_address;
  ca_address.region_code = "US";
  ca_address.administrative_area = "CA";
  ca_key.FromAddress(ca_address);
  const Rule* rule = supplier_.GetRule(ca_key);
  ASSERT_TRUE(rule != NULL);
  EXPECT_EQ("data/US/CA", rule->GetId());
}

TEST_F(PreloadSupplierTest, GetZwRule) {
  supplier_.LoadRules("ZW", *loaded_callback_);
  LookupKey zw_key;
  AddressData zw_address;
  zw_address.region_code = "ZW";
  zw_key.FromAddress(zw_address);
  const Rule* rule = supplier_.GetRule(zw_key);
  ASSERT_TRUE(rule != NULL);
  EXPECT_EQ("data/ZW", rule->GetId());
}

TEST_F(PreloadSupplierTest, GetUnknownRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey unknown_key;
  AddressData unknown_address;
  unknown_address.region_code = "US";
  unknown_address.administrative_area = "ZZ";
  unknown_key.FromAddress(unknown_address);
  const Rule* rule = supplier_.GetRule(unknown_key);
  EXPECT_TRUE(rule == NULL);
}

TEST_F(PreloadSupplierTest, GetTooPreciseRule) {
  supplier_.LoadRules("US", *loaded_callback_);
  LookupKey precise_key;
  AddressData precise_address;
  precise_address.region_code = "US";
  precise_address.administrative_area = "CA";
  precise_address.locality = "Mountain View";
  precise_key.FromAddress(precise_address);
  const Rule* rule = supplier_.GetRule(precise_key);
  EXPECT_TRUE(rule == NULL);
}

TEST_F(PreloadSupplierTest, GetRulesForRegion) {
  supplier_.LoadRules("CN", *loaded_callback_);
  const std::map<std::string, const Rule*>& rules =
      supplier_.GetRulesForRegion("CN");
  EXPECT_TRUE(rules.find("data/CN") != rules.end());
  EXPECT_LT(1U, rules.size());
}

}  // namespace
