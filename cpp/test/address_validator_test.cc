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
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <utility>

#include <gtest/gtest.h>

#include "fake_downloader.h"

namespace {

using i18n::addressinput::AddressData;
using i18n::addressinput::AddressValidator;
using i18n::addressinput::BuildCallback;
using i18n::addressinput::FakeDownloader;
using i18n::addressinput::FieldProblemMap;
using i18n::addressinput::NullStorage;
using i18n::addressinput::scoped_ptr;

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

class AddressValidatorTest : public testing::Test {
 protected:
  AddressValidatorTest()
      : address_(),
        allow_postal_(false),
        require_name_(false),
        filter_(),
        problems_(),
        expected_(),
        called_(false),
        validator_(FakeDownloader::kFakeDataUrl,
                   new FakeDownloader,
                   new NullStorage),
        validated_(BuildCallback(this, &AddressValidatorTest::Validated)) {}

  virtual ~AddressValidatorTest() {}

  void Validate() {
    validator_.Validate(
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

  const AddressValidator validator_;
  const scoped_ptr<const AddressValidator::Callback> validated_;

  DISALLOW_COPY_AND_ASSIGN(AddressValidatorTest);
};

TEST_F(AddressValidatorTest, EmptyAddress) {
  expected_.insert(std::make_pair(COUNTRY, MISSING_REQUIRED_FIELD));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_F(AddressValidatorTest, InvalidCountry) {
  address_.region_code = "QZ";

  expected_.insert(std::make_pair(COUNTRY, UNKNOWN_VALUE));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_F(AddressValidatorTest, ValidAddressUS) {
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

TEST_F(AddressValidatorTest, InvalidAddressUS) {
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

TEST_F(AddressValidatorTest, ValidAddressCH) {
  address_.region_code = "CH";
  address_.locality = "ZH";  /* Zürich */
  address_.postal_code = "8002";
  address_.address_line.push_back("Brandschenkestrasse 110");
  address_.language_code = "de";

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_F(AddressValidatorTest, InvalidAddressCH) {
  address_.region_code = "CH";
  address_.postal_code = "123";

  expected_.insert(std::make_pair(STREET_ADDRESS, MISSING_REQUIRED_FIELD));
  expected_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));
  expected_.insert(std::make_pair(LOCALITY, MISSING_REQUIRED_FIELD));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_F(AddressValidatorTest, ValidPostalCodeMX) {
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

TEST_F(AddressValidatorTest, MismatchingPostalCodeMX) {
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

TEST_F(AddressValidatorTest, ValidateFilter) {
  address_.region_code = "CH";
  address_.postal_code = "123";

  filter_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));

  expected_.insert(std::make_pair(POSTAL_CODE, INVALID_FORMAT));

  ASSERT_NO_FATAL_FAILURE(Validate());
  ASSERT_TRUE(called_);
  EXPECT_EQ(expected_, problems_);
}

TEST_F(AddressValidatorTest, ValidateClearsProblems) {
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

}  // namespace
