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

#include <memory>
#include <string>

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
using i18n::addressinput::TestdataSource;

using i18n::addressinput::ADMIN_AREA;
using i18n::addressinput::COUNTRY;
using i18n::addressinput::DEPENDENT_LOCALITY;
using i18n::addressinput::LOCALITY;
using i18n::addressinput::POSTAL_CODE;
using i18n::addressinput::STREET_ADDRESS;

using i18n::addressinput::INVALID_FORMAT;
using i18n::addressinput::MISMATCHING_VALUE;
using i18n::addressinput::MISSING_REQUIRED_FIELD;
using i18n::addressinput::UNEXPECTED_FIELD;
using i18n::addressinput::UNKNOWN_VALUE;
using i18n::addressinput::UNSUPPORTED_FIELD;

class ValidatorWrapper {
 public:
  virtual ~ValidatorWrapper() = default;
  virtual void Validate(const AddressData& address, bool allow_postal,
                        bool require_name, const FieldProblemMap* filter,
                        FieldProblemMap* problems,
                        const AddressValidator::Callback& validated) = 0;
};

class OndemandValidatorWrapper : public ValidatorWrapper {
 public:
  OndemandValidatorWrapper(const OndemandValidatorWrapper&) = delete;
  OndemandValidatorWrapper& operator=(const OndemandValidatorWrapper&) = delete;

  static ValidatorWrapper* Build() { return new OndemandValidatorWrapper; }

  void Validate(const AddressData& address, bool allow_postal,
                bool require_name, const FieldProblemMap* filter,
                FieldProblemMap* problems,
                const AddressValidator::Callback& validated) override {
    validator_.Validate(address, allow_postal, require_name, filter, problems,
                        validated);
  }

 private:
  OndemandValidatorWrapper()
      : supplier_(new TestdataSource(false), new NullStorage),
        validator_(&supplier_) {}

  OndemandSupplier supplier_;
  const AddressValidator validator_;
};

class PreloadValidatorWrapper : public ValidatorWrapper {
 public:
  PreloadValidatorWrapper(const PreloadValidatorWrapper&) = delete;
  PreloadValidatorWrapper& operator=(const PreloadValidatorWrapper&) = delete;

  static ValidatorWrapper* Build() { return new PreloadValidatorWrapper; }

  void Validate(const AddressData& address, bool allow_postal,
                bool require_name, const FieldProblemMap* filter,
                FieldProblemMap* problems,
                const AddressValidator::Callback& validated) override {
    const std::string& region_code = address.region_code;
    if (!region_code.empty() && !supplier_.IsLoaded(region_code)) {
      supplier_.LoadRules(region_code, *loaded_);
    }
    validator_.Validate(address, allow_postal, require_name, filter, problems,
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
  const std::unique_ptr<const PreloadSupplier::Callback> loaded_;
};

class AddressValidatorTest
    : public testing::TestWithParam<ValidatorWrapper* (*)()> {
 public:
  AddressValidatorTest(const AddressValidatorTest&) = delete;
  AddressValidatorTest& operator=(const AddressValidatorTest&) = delete;

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
    validator_wrapper_->Validate(address_, allow_postal_, require_name_,
                                 &filter_, &problems_, *validated_);
  }

  AddressData address_;
  bool allow_postal_;
  bool require_name_;
  FieldProblemMap filter_;
  FieldProblemMap problems_;
  FieldProblemMap expected_;
  bool called_;

 private:
  void Validated(bool success, const AddressData& address,
                 const FieldProblemMap& problems) {
    ASSERT_TRUE(success);
    ASSERT_EQ(&address_, &address);
    ASSERT_EQ(&problems_, &problems);
    called_ = true;
  }

  const std::unique_ptr<ValidatorWrapper> validator_wrapper_;
  const std::unique_ptr<const AddressValidator::Callback> validated_;
};

INSTANTIATE_TEST_SUITE_P(OndemandSupplier, AddressValidatorTest,
                         testing::Values(&OndemandValidatorWrapper::Build));

INSTANTIATE_TEST_SUITE_P(PreloadSupplier, AddressValidatorTest,
                         testing::Values(&PreloadValidatorWrapper::Build));

TEST_P(AddressValidatorTest, EmptyAddress) {
  expected_ = {{COUNTRY, MISSING_REQUIRED_FIELD}};

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, InvalidCountry) {
  address_ = {.region_code = "QZ"};

  expected_ = {{COUNTRY, UNKNOWN_VALUE}};

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressUS) {
  address_ = {
      .region_code = "US",
      .address_line{"1600 Amphitheatre Parkway"},
      .administrative_area = "CA",  // California
      .locality = "Mountain View",
      .postal_code = "94043",
      .language_code = "en",
  };

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_ = {
        {LOCALITY, UNSUPPORTED_FIELD},
        {DEPENDENT_LOCALITY, UNSUPPORTED_FIELD},
    };
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, InvalidAddressUS) {
  address_ = {
      .region_code = "US",
      .postal_code = "123",
  };

  expected_ = {
      {ADMIN_AREA, MISSING_REQUIRED_FIELD},
      {LOCALITY, MISSING_REQUIRED_FIELD},
      {STREET_ADDRESS, MISSING_REQUIRED_FIELD},
      {POSTAL_CODE, INVALID_FORMAT},
  };

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_.emplace(DEPENDENT_LOCALITY, UNSUPPORTED_FIELD);
    expected_.emplace(LOCALITY, UNSUPPORTED_FIELD);
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressCH) {
  address_ = {
      .region_code = "CH",
      .address_line{"Brandschenkestrasse 110"},
      .locality = "ZH",  // Zürich
      .postal_code = "8002",
      .language_code = "de",
  };

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_ = {
        {LOCALITY, UNSUPPORTED_FIELD},
        {DEPENDENT_LOCALITY, UNSUPPORTED_FIELD},
    };
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, InvalidAddressCH) {
  address_ = {
      .region_code = "CH",
      .postal_code = "123",
  };

  expected_ = {
      {STREET_ADDRESS, MISSING_REQUIRED_FIELD},
      {POSTAL_CODE, INVALID_FORMAT},
      {LOCALITY, MISSING_REQUIRED_FIELD},
  };

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_.emplace(LOCALITY, UNSUPPORTED_FIELD);
    expected_.emplace(DEPENDENT_LOCALITY, UNSUPPORTED_FIELD);
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidPostalCodeMX) {
  address_ = {
      .region_code = "MX",
      .address_line{"Av Gregorio Méndez Magaña 1400"},
      .administrative_area = "TAB",  // Tabasco
      .locality = "Villahermosa",
      .postal_code = "86070",
      .language_code = "es",
  };

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_ = {
        {DEPENDENT_LOCALITY, UNSUPPORTED_FIELD},
        {LOCALITY, UNSUPPORTED_FIELD},
    };
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, MismatchingPostalCodeMX) {
  address_ = {
      .region_code = "MX",
      .address_line{"Av Gregorio Méndez Magaña 1400"},
      .administrative_area = "TAB",  // Tabasco
      .locality = "Villahermosa",
      .postal_code = "80000",
      .language_code = "es",
  };

  expected_ = {{POSTAL_CODE, MISMATCHING_VALUE}};

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_.emplace(LOCALITY, UNSUPPORTED_FIELD);
    expected_.emplace(DEPENDENT_LOCALITY, UNSUPPORTED_FIELD);
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidateFilter) {
  address_ = {
      .region_code = "CH",
      .postal_code = "123",
  };

  filter_ = {{POSTAL_CODE, INVALID_FORMAT}};

  expected_ = {{POSTAL_CODE, INVALID_FORMAT}};

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidateClearsProblems) {
  address_ = {
      .region_code = "CH",
      .address_line{"Brandschenkestrasse 110"},
      .locality = "ZH",  // Zürich
      .postal_code = "123",
      .language_code = "de",
  };

  problems_ = {
      {LOCALITY, UNEXPECTED_FIELD},
      {LOCALITY, MISSING_REQUIRED_FIELD},
      {STREET_ADDRESS, MISSING_REQUIRED_FIELD},
  };

  expected_ = {{POSTAL_CODE, INVALID_FORMAT}};

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_.emplace(LOCALITY, UNSUPPORTED_FIELD);
    expected_.emplace(DEPENDENT_LOCALITY, UNSUPPORTED_FIELD);
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidKanjiAddressJP) {
  address_ = {
      .region_code = "JP",
      .address_line{"徳島市..."},
      .administrative_area = "徳島県",
      .postal_code = "770-0847",
      .language_code = "ja",
  };

  if (GetParam() == &PreloadValidatorWrapper::Build) {
    expected_ = {
        {DEPENDENT_LOCALITY, UNSUPPORTED_FIELD},
        {LOCALITY, UNSUPPORTED_FIELD},
    };
  }

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidLatinAddressJP) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map Latin script names to local script names.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_ = {
      .region_code = "JP",
      .address_line{"...Tokushima"},
      .administrative_area = "Tokushima",
      .postal_code = "770-0847",
      .language_code = "ja-Latn",
  };

  expected_ = {
      {DEPENDENT_LOCALITY, UNSUPPORTED_FIELD},
      {LOCALITY, UNSUPPORTED_FIELD},
  };

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressBR) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map natural language names to metadata IDs.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_ = {
      .region_code = "BR",
      .address_line{"Rodovia Raposo Tavares, 6388-6682"},
      .administrative_area = "São Paulo",
      .locality = "Presidente Prudente",
      .postal_code = "19063-008",
      .language_code = "pt",
  };

  expected_ = {{DEPENDENT_LOCALITY, UNSUPPORTED_FIELD}};

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressCA_en) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map natural language names to metadata IDs.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_ = {
      .region_code = "CA",
      .address_line{"..."},
      .administrative_area = "New Brunswick",
      .locality = "Saint John County",
      .postal_code = "E2L 4Z6",
      .language_code = "en",
  };

  expected_ = {
      {DEPENDENT_LOCALITY, UNSUPPORTED_FIELD},
      {LOCALITY, UNSUPPORTED_FIELD},
  };

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_P(AddressValidatorTest, ValidAddressCA_fr) {
  // Skip this test case when using the OndemandSupplier, which depends on the
  // address metadata server to map natural language names to metadata IDs.
  if (GetParam() == &OndemandValidatorWrapper::Build) return;

  address_ = {
      .region_code = "CA",
      .address_line{"..."},
      .administrative_area = "Nouveau-Brunswick",
      .locality = "Comté de Saint-Jean",
      .postal_code = "E2L 4Z6",
      .language_code = "fr",
  };

  expected_ = {
      {DEPENDENT_LOCALITY, UNSUPPORTED_FIELD},
      {LOCALITY, UNSUPPORTED_FIELD},
  };

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

}  // namespace
