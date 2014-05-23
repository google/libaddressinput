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
#include <libaddressinput/region_data.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include "fake_downloader.h"
#include "lookup_key.h"
#include "rule.h"

#include <cstddef>
#include <string>

#include <gtest/gtest.h>

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::BuildCallback;
using i18n::addressinput::FakeDownloader;
using i18n::addressinput::LookupKey;
using i18n::addressinput::NullStorage;
using i18n::addressinput::PreloadSupplier;
using i18n::addressinput::RegionData;
using i18n::addressinput::Rule;
using i18n::addressinput::scoped_ptr;

class PreloadSupplierTest : public testing::Test {
 protected:
  PreloadSupplierTest()
      : supplier_(FakeDownloader::kFakeAggregateDataUrl,
                  new FakeDownloader,
                  new NullStorage),
        loaded_callback_(BuildCallback(this, &PreloadSupplierTest::OnLoaded)),
        best_language_() {}

  ~PreloadSupplierTest() {}

  PreloadSupplier supplier_;
  scoped_ptr<PreloadSupplier::Callback> loaded_callback_;
  std::string best_language_;

 private:
  void OnLoaded(bool success,
                const std::string& region_code,
                const int& num_rules) {
    EXPECT_TRUE(success);
    EXPECT_FALSE(region_code.empty());
    EXPECT_LT(0, num_rules);
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

TEST_F(PreloadSupplierTest, BuildUsRegionTree) {
  supplier_.LoadRules("US", *loaded_callback_);
  const RegionData& tree =
      supplier_.BuildRegionTree("US", "en-US", &best_language_);
  EXPECT_FALSE(tree.sub_regions().empty());
}

TEST_F(PreloadSupplierTest, BuildCnRegionTree) {
  supplier_.LoadRules("CN", *loaded_callback_);
  const RegionData& tree =
      supplier_.BuildRegionTree("CN", "zh-Hans", &best_language_);
  ASSERT_FALSE(tree.sub_regions().empty());
  EXPECT_FALSE(tree.sub_regions().front()->sub_regions().empty());
}

TEST_F(PreloadSupplierTest, BuildChRegionTree) {
  supplier_.LoadRules("CH", *loaded_callback_);
  const RegionData& tree =
      supplier_.BuildRegionTree("CH", "de-CH", &best_language_);
  // Although "CH" has information for its administrative divisions, the
  // administrative area field is not used, which results in an empty tree of
  // sub-regions.
  EXPECT_TRUE(tree.sub_regions().empty());
}

TEST_F(PreloadSupplierTest, BuildZwRegionTree) {
  supplier_.LoadRules("ZW", *loaded_callback_);
  const RegionData& tree =
      supplier_.BuildRegionTree("ZW", "en-ZW", &best_language_);
  EXPECT_TRUE(tree.sub_regions().empty());
}

}  // namespace
