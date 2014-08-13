// Copyright (C) 2013 Google Inc.
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

#include "validating_storage.h"

#include <libaddressinput/callback.h>
#include <libaddressinput/storage.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <cstddef>
#include <string>

#include <gtest/gtest.h>

#include "fake_storage.h"

#define CHECKSUM "dd63dafcbd4d5b28badfcaf86fb6fcdb"
#define DATA "{'foo': 'bar'}"
#define OLD_TIMESTAMP "0"

namespace {

using i18n::addressinput::BuildCallback;
using i18n::addressinput::FakeStorage;
using i18n::addressinput::scoped_ptr;
using i18n::addressinput::Storage;
using i18n::addressinput::ValidatingStorage;

const char kKey[] = "key";
const char kValidatedData[] = DATA;
const char kStaleWrappedData[] = "timestamp=" OLD_TIMESTAMP "\n"
                                 "checksum=" CHECKSUM "\n"
                                 DATA;
const char kEmptyData[] = "";

// Tests for ValidatingStorage object.
class ValidatingStorageTest : public testing::Test {
 protected:
  ValidatingStorageTest()
      : wrapped_storage_(new FakeStorage),
        storage_(wrapped_storage_),
        success_(false),
        key_(),
        data_(),
        data_ready_(BuildCallback(this, &ValidatingStorageTest::OnDataReady)) {}

  Storage* const wrapped_storage_;  // Owned by |storage_|.
  ValidatingStorage storage_;
  bool success_;
  std::string key_;
  std::string data_;
  const scoped_ptr<const ValidatingStorage::Callback> data_ready_;

 private:
  void OnDataReady(bool success, const std::string& key, std::string* data) {
    ASSERT_FALSE(success && data == NULL);
    success_ = success;
    key_ = key;
    if (data != NULL) {
      data_ = *data;
      delete data;
    }
  }

  DISALLOW_COPY_AND_ASSIGN(ValidatingStorageTest);
};

TEST_F(ValidatingStorageTest, GoodData) {
  storage_.Put(kKey, new std::string(kValidatedData));
  storage_.Get(kKey, *data_ready_);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_EQ(kValidatedData, data_);
}

TEST_F(ValidatingStorageTest, EmptyData) {
  storage_.Put(kKey, new std::string(kEmptyData));
  storage_.Get(kKey, *data_ready_);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_EQ(kEmptyData, data_);
}

TEST_F(ValidatingStorageTest, MissingKey) {
  storage_.Get(kKey, *data_ready_);

  EXPECT_FALSE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_TRUE(data_.empty());
}

TEST_F(ValidatingStorageTest, GarbageData) {
  storage_.Put(kKey, new std::string(kValidatedData));
  wrapped_storage_->Put(kKey, new std::string("garbage"));
  storage_.Get(kKey, *data_ready_);

  EXPECT_FALSE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_TRUE(data_.empty());
}

TEST_F(ValidatingStorageTest, StaleData) {
  storage_.Put(kKey, new std::string(kValidatedData));
  wrapped_storage_->Put(kKey, new std::string(kStaleWrappedData));
  storage_.Get(kKey, *data_ready_);

  EXPECT_FALSE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_EQ(kValidatedData, data_);
}

}  // namespace
