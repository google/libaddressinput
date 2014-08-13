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

#include <libaddressinput/address_validator.h>

#include <libaddressinput/address_data.h>
#include <libaddressinput/address_field.h>
#include <libaddressinput/address_problem.h>
#include <libaddressinput/callback.h>
#include <libaddressinput/null_storage.h>
#include <libaddressinput/ondemand_supplier.h>
#include <libaddressinput/preload_supplier.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>
#include <utility>

#include <gtest/gtest.h>

#include "testdata_source.h"

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::AddressValidator;
using i18n::addressinput::BuildCallback;
using i18n::addressinput::FieldProblemMap;
using i18n::addressinput::NullStorage;
using i18n::addressinput::OndemandSupplier;
using i18n::addressinput::PreloadSupplier;
using i18n::addressinput::scoped_ptr;
using i18n::addressinput::TestdataSource;

using i18n::addressinput::COUNTRY;
using i18n::addressinput::ADMIN_AREA;
using i18n::addressinput::LOCALITY;
using i18n::addressinput::POSTAL_CODE;
using i18n::addressinput::STREET_ADDRESS;

using i18n::addressinput::UNEXPECTED_FIELD;
using i18n::addressinput::MISSING_REQUIRED_FIELD;
using i18n::addressinput::UNKNOWN_VALUE;
using i18n::addressinput::INVALID_FORMAT;
using i18n::addressinput::MISMATCHING_VALUE;

class ValidatorWrapper {
 public:
  virtual ~ValidatorWrapper() {}
  virtual void Validate(const AddressData& address,
                        bool allow_postal,
                        bool require_name,
                        const FieldProblemMap* filter,
                        FieldProblemMap* problems,
                        const AddressValidator::Callback& validated) = 0;
};

class OndemandValidatorWrapper : public ValidatorWrapper {
 public:
  static ValidatorWrapper* Build() { return new OndemandValidatorWrapper; }

  virtual void Validate(const AddressData& address,
                        bool allow_postal,
                        bool require_name,
                        const FieldProblemMap* filter,
                        FieldProblemMap* problems,
                        const AddressValidator::Callback& validated) {
    validator_.Validate(
        address,
        allow_postal,
        require_name,
        filter,
        problems,
        validated);
  }

 private:
  OndemandValidatorWrapper()
      : supplier_(new TestdataSource(false), new NullStorage),
        validator_(&supplier_) {}

  OndemandSupplier supplier_;
  const AddressValidator validator_;
  DISALLOW_COPY_AND_ASSIGN(OndemandValidatorWrapper);
};

class PreloadValidatorWrapper : public ValidatorWrapper {
 public:
  static ValidatorWrapper* Build() { return new PreloadValidatorWrapper; }

  virtual void Validate(const AddressData& address,
                        bool allow_postal,
                        bool require_name,
                        const FieldProblemMap* filter,
                        FieldProblemMap* problems,
                        const AddressValidator::Callback& validated) {
    const std::string& region_code = address.region_code;
    if (!region_code.empty() && !supplier_.IsLoaded(region_code)) {
      supplier_.LoadRules(region_code, *loaded_);
    }
    validator_.Validate(
        address,
        allow_postal,
        require_name,
        filter,
        problems,
        validated);
  }

 private:
  PreloadValidatorWrapper()
      : supplier_(new TestdataSource(true), new NullStorage),
        validator_(&supplier_),
        loaded_(BuildCallback(this, &PreloadValidatorWrapper::Loaded)) {}

  void Loaded(bool success, const std::string&, int) { ASSERT_TRUE(success); }

  PreloadSupplier supplier_;
  const AddressValidator validator_;
  const scoped_ptr<const PreloadSupplier::Callback> loaded_;
  DISALLOW_COPY_AND_ASSIGN(PreloadValidatorWrapper);
};

class AddressValidatorTest
    : public testing::TestWithParam<ValidatorWrapper* (*)()> {
 protected:
  AddressValidatorTest()
      : address_(),
        allow_postal_(false),
        require_name_(false),
        filter_(),
        problems_(),
        expected_(),
        called_(false),
        validator_wrapper_((*GetParam())()),
        validated_(BuildCallback(this, &AddressValidatorTest::Validated)) {}

  void Validate() {
    validator_wrapper_->Validate(
        address_,
        allow_postal_,
        require_name_,
        &filter_,
        &problems_,
        *validated_);
  }

  AddressData address_;
  bool allow_postal_;
  bool require_name_;
  FieldProblemMap filter_;
  FieldProblemMap problems_;
  FieldProblemMap expected_;
  bool called_;

 private:
  void Validated(bool success,
                 const AddressData& address,
                 const FieldProblemMap& problems) {
    ASSERT_TRUE(success);
    ASSERT_EQ(&address_, &address);
    ASSERT_EQ(&problems_, &problems);
    called_ = true;
  }

  const scoped_ptr<ValidatorWrapper> validator_wrapper_;
  const scoped_ptr<const AddressValidator::Callback> validated_;

  DISALLOW_COPY_AND_ASSIGN(AddressValidatorTest);
};

INSTANTIATE_TEST_CASE_P(OndemandSupplier,
                        AddressValidatorTest,
                        testing::Values(&OndemandValidatorWrapper::Build));

INSTANTIATE_TEST_CASE_P(PreloadSupplier,
                        AddressValidatorTest,
                        testing::Values(&PreloadValidatorWrapper::Build));

TEST_P(AddressValidatorTest, EmptyAddress) {
  expected_.insert(std::make_pair(COUNTRY, MISSING_REQUIRED_FIELD));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, InvalidCountry) {
  address_.region_code = "QZ";

  expected_.insert(std::make_pair(COUNTRY, UNKNOWN_VALUE));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressUS) {
  address_.region_code = "US";
  address_.administrative_area = "CA";  // California
  address_.locality = "Mountain View";
  address_.postal_code = "94043";
  address_.address_line.push_back("1600 Amphitheatre Parkway");
  address_.language_code = "en";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, InvalidAddressUS) {
  address_.region_code = "US";
  address_.postal_code = "123";

  expected_.insert(std::make_pair(ADMIN_AREA, MISSING_REQUIRED_FIELD));
  expected_.insert(std::make_pair(LOCALITY, MISSING_REQUIRED_FIELD));
  expected_.insert(std::make_pair(STREET_ADDRESS, MISSING_REQUIRED_FIELD));
  expected_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressCH) {
  address_.region_code = "CH";
  address_.locality = "ZH";  /* Zürich */
  address_.postal_code = "8002";
  address_.address_line.push_back("Brandschenkestrasse 110");
  address_.language_code = "de";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, InvalidAddressCH) {
  address_.region_code = "CH";
  address_.postal_code = "123";

  expected_.insert(std::make_pair(STREET_ADDRESS, MISSING_REQUIRED_FIELD));
  expected_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));
  expected_.insert(std::make_pair(LOCALITY, MISSING_REQUIRED_FIELD));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidPostalCodeMX) {
  address_.region_code = "MX";
  address_.locality = "Villahermosa";
  address_.administrative_area = "TAB";  // Tabasco
  address_.postal_code = "86070";
  address_.address_line.push_back(
      /* Av Gregorio Méndez Magaña 1400 */
      "Av Gregorio M\xC3\xA9ndez Maga\xC3\xB1""a 1400");
  address_.language_code = "es";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, MismatchingPostalCodeMX) {
  address_.region_code = "MX";
  address_.locality = "Villahermosa";
  address_.administrative_area = "TAB";  // Tabasco
  address_.postal_code = "80000";
  address_.address_line.push_back(
      /* Av Gregorio Méndez Magaña 1400 */
      "Av Gregorio M\xC3\xA9ndez Maga\xC3\xB1""a 1400");
  address_.language_code = "es";

  expected_.insert(std::make_pair(POSTAL_CODE, MISMATCHING_VALUE));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidateFilter) {
  address_.region_code = "CH";
  address_.postal_code = "123";

  filter_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));

  expected_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidateClearsProblems) {
  address_.region_code = "CH";
  address_.locality = "ZH";  /* Zürich */
  address_.postal_code = "123";
  address_.address_line.push_back("Brandschenkestrasse 110");
  address_.language_code = "de";

  problems_.insert(std::make_pair(LOCALITY, UNEXPECTED_FIELD));
  problems_.insert(std::make_pair(LOCALITY, MISSING_REQUIRED_FIELD));
  problems_.insert(std::make_pair(STREET_ADDRESS, MISSING_REQUIRED_FIELD));

  expected_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidKanjiAddressJP) {
  address_.region_code = "JP";
  address_.administrative_area =
      "\xE5\xBE\xB3\xE5\xB3\xB6\xE7\x9C\x8C"; /* 徳島県 */
  address_.locality =
      "\xE5\xBE\xB3\xE5\xB3\xB6\xE5\xB8\x82";  /* 徳島市 */
  address_.postal_code = "770-0847";
  address_.address_line.push_back("...");
  address_.language_code = "ja";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidLatinAddressJP) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map Latin script names to local script names.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_.region_code = "JP";
  address_.administrative_area = "Tokushima";
  address_.locality = "Tokushima";
  address_.postal_code = "770-0847";
  address_.address_line.push_back("...");
  address_.language_code = "ja-Latn";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressBR) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map natural language names to metadata IDs.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_.region_code = "BR";
  address_.administrative_area = "S\xC3\xA3o Paulo";  /* São Paulo */
  address_.locality = "Presidente Prudente";
  address_.postal_code = "19063-008";
  address_.address_line.push_back("Rodovia Raposo Tavares, 6388-6682");
  address_.language_code = "pt";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressCA_en) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map natural language names to metadata IDs.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_.region_code = "CA";
  address_.administrative_area = "New Brunswick";
  address_.locality = "Saint John County";
  address_.postal_code = "E2L 4Z6";
  address_.address_line.push_back("...");
  address_.language_code = "en";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressCA_fr) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map natural language names to metadata IDs.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_.region_code = "CA";
  address_.administrative_area = "Nouveau-Brunswick";
  address_.locality = "Comt\xC3\xA9 de Saint-Jean";  /* Comté de Saint-Jean */
  address_.postal_code = "E2L 4Z6";
  address_.address_line.push_back("...");
  address_.language_code = "fr";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

}  // namespace
