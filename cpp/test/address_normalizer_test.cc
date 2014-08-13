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

#include <libaddressinput/address_normalizer.h>

#include <libaddressinput/address_data.h>
#include <libaddressinput/callback.h>
#include <libaddressinput/null_storage.h>
#include <libaddressinput/preload_supplier.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include <gtest/gtest.h>

#include "testdata_source.h"

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::AddressNormalizer;
using i18n::addressinput::BuildCallback;
using i18n::addressinput::NullStorage;
using i18n::addressinput::PreloadSupplier;
using i18n::addressinput::scoped_ptr;
using i18n::addressinput::TestdataSource;

class AddressNormalizerTest : public testing::Test {
 protected:
  AddressNormalizerTest()
      : supplier_(new TestdataSource(true), new NullStorage),
        loaded_(BuildCallback(this, &AddressNormalizerTest::OnLoaded)),
        normalizer_(&supplier_) {}

  PreloadSupplier supplier_;
  const scoped_ptr<const PreloadSupplier::Callback> loaded_;
  const AddressNormalizer normalizer_;

 private:
  void OnLoaded(bool success, const std::string& region_code, int num_rules) {
    ASSERT_TRUE(success);
    ASSERT_FALSE(region_code.empty());
    ASSERT_LT(0, num_rules);
  }

  DISALLOW_COPY_AND_ASSIGN(AddressNormalizerTest);
};

TEST_F(AddressNormalizerTest, CaliforniaShortNameCa) {
  supplier_.LoadRules("US", *loaded_);
  AddressData address;
  address.language_code = "en-US";
  address.region_code = "US";
  address.administrative_area = "California";
  address.locality = "Mountain View";
  normalizer_.Normalize(&address);
  EXPECT_EQ("CA", address.administrative_area);
}

TEST_F(AddressNormalizerTest, GangwonLatinNameStaysUnchanged) {
  supplier_.LoadRules("KR", *loaded_);
  AddressData address;
  address.language_code = "ko-Latn";
  address.region_code = "KR";
  address.administrative_area = "Gangwon";
  normalizer_.Normalize(&address);
  EXPECT_EQ("Gangwon", address.administrative_area);
}

TEST_F(AddressNormalizerTest, GangwonKoreanName) {
  supplier_.LoadRules("KR", *loaded_);
  AddressData address;
  address.language_code = "ko-KR";
  address.region_code = "KR";
  address.administrative_area = "\xEA\xB0\x95\xEC\x9B\x90";  /* "강원" */
  normalizer_.Normalize(&address);
  EXPECT_EQ(
      "\xEA\xB0\x95\xEC\x9B\x90\xEB\x8F\x84",  /* "강원도" */
      address.administrative_area);
}

TEST_F(AddressNormalizerTest, DontSwitchLatinScriptForUnknownLanguage) {
  supplier_.LoadRules("KR", *loaded_);
  AddressData address;
  address.region_code = "KR";
  address.administrative_area = "Gangwon";
  normalizer_.Normalize(&address);
  EXPECT_EQ("Gangwon", address.administrative_area);
}

TEST_F(AddressNormalizerTest, DontSwitchLocalScriptForUnknownLanguage) {
  supplier_.LoadRules("KR", *loaded_);
  AddressData address;
  address.region_code = "KR";
  address.administrative_area = "\xEA\xB0\x95\xEC\x9B\x90";  /* "강원" */
  normalizer_.Normalize(&address);
  EXPECT_EQ(
      "\xEA\xB0\x95\xEC\x9B\x90\xEB\x8F\x84",  /* "강원도" */
      address.administrative_area);
}

}  // namespace
