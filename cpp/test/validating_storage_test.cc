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
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include <gtest/gtest.h>

#include "fake_storage.h"

namespace {

using i18n::addressinput::BuildCallback;
using i18n::addressinput::FakeStorage;
using i18n::addressinput::scoped_ptr;
using i18n::addressinput::Storage;
using i18n::addressinput::ValidatingStorage;

// Tests for ValidatingStorage object.
class ValidatingStorageTest : public testing::Test  {
 protected:
  ValidatingStorageTest()
      : wrapped_storage_(new FakeStorage),
        storage_(wrapped_storage_),
        success_(false),
        key_(),
        data_() {}

  virtual ~ValidatingStorageTest() {}

  Storage::Callback* BuildCallback() {
    return ::BuildCallback(this, &ValidatingStorageTest::OnDataReady);
  }

  FakeStorage* const wrapped_storage_;  // Owned by |storage_|.
  ValidatingStorage storage_;
  bool success_;
  std::string key_;
  std::string data_;

 private:
  void OnDataReady(bool success,
                   const std::string& key,
                   const std::string& data) {
    success_ = success;
    key_ = key;
    data_ = data;
  }
};

TEST_F(ValidatingStorageTest, Basic) {
  storage_.Put("key", "value");

  scoped_ptr<Storage::Callback> callback(BuildCallback());
  storage_.Get("key", *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ("key", key_);
  EXPECT_EQ("value", data_);
}

TEST_F(ValidatingStorageTest, EmptyData) {
  storage_.Put("key", std::string());

  scoped_ptr<Storage::Callback> callback(BuildCallback());
  storage_.Get("key", *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ("key", key_);
  EXPECT_TRUE(data_.empty());
}

TEST_F(ValidatingStorageTest, MissingKey) {
  scoped_ptr<Storage::Callback> callback(BuildCallback());
  storage_.Get("key", *callback);

  EXPECT_FALSE(success_);
  EXPECT_EQ("key", key_);
  EXPECT_TRUE(data_.empty());
}

TEST_F(ValidatingStorageTest, GarbageData) {
  storage_.Put("key", "value");
  wrapped_storage_->Put("key", "garbage");

  scoped_ptr<Storage::Callback> callback(BuildCallback());
  storage_.Get("key", *callback);

  EXPECT_FALSE(success_);
  EXPECT_EQ("key", key_);
  EXPECT_TRUE(data_.empty());
}

}  // namespace
