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

#include "retriever.h"

#include <libaddressinput/callback.h>
#include <libaddressinput/null_storage.h>
#include <libaddressinput/storage.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include <gtest/gtest.h>

#include "fake_downloader.h"
#include "mock_downloader.h"

#define CHECKSUM "dd63dafcbd4d5b28badfcaf86fb6fcdb"
#define DATA "{'foo': 'bar'}"
#define OLD_TIMESTAMP "0"

namespace {

using i18n::addressinput::BuildCallback;
using i18n::addressinput::FakeDownloader;
using i18n::addressinput::MockDownloader;
using i18n::addressinput::NullStorage;
using i18n::addressinput::Retriever;
using i18n::addressinput::Storage;
using i18n::addressinput::scoped_ptr;

const char kKey[] = "data/CA/AB--fr";

// Empty data that the downloader can return.
const char kEmptyData[] = "{}";

// The value of the data that the stale storage returns.
const char kStaleData[] = DATA;

// The actual data that the stale storage returns.
const char kStaleWrappedData[] = "timestamp=" OLD_TIMESTAMP "\n"
                                 "checksum=" CHECKSUM "\n"
                                 DATA;

// Tests for Retriever object.
class RetrieverTest : public testing::Test {
 protected:
  RetrieverTest()
      : retriever_(FakeDownloader::kFakeDataUrl,
                   new FakeDownloader,
                   new NullStorage),
        success_(false),
        key_(),
        data_() {}

  virtual ~RetrieverTest() {}

  Retriever::Callback* BuildCallback() {
    return ::BuildCallback(this, &RetrieverTest::OnDataReady);
  }

  Retriever retriever_;
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

TEST_F(RetrieverTest, RetrieveData) {
  scoped_ptr<Retriever::Callback> callback(BuildCallback());
  retriever_.Retrieve(kKey, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_FALSE(data_.empty());
  EXPECT_NE(kEmptyData, data_);
}

TEST_F(RetrieverTest, ReadDataFromStorage) {
  scoped_ptr<Retriever::Callback> callback1(BuildCallback());
  retriever_.Retrieve(kKey, *callback1);

  scoped_ptr<Retriever::Callback> callback2(BuildCallback());
  retriever_.Retrieve(kKey, *callback2);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_FALSE(data_.empty());
  EXPECT_NE(kEmptyData, data_);
}

TEST_F(RetrieverTest, MissingKeyReturnsEmptyData) {
  static const char kMissingKey[] = "junk";

  scoped_ptr<Retriever::Callback> callback(BuildCallback());
  retriever_.Retrieve(kMissingKey, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kMissingKey, key_);
  EXPECT_EQ(kEmptyData, data_);
}

TEST_F(RetrieverTest, FaultyDownloader) {
  // An empty MockDownloader will fail for any request.
  Retriever bad_retriever(MockDownloader::kMockDataUrl,
                          new MockDownloader,
                          new NullStorage);

  scoped_ptr<Retriever::Callback> callback(BuildCallback());
  bad_retriever.Retrieve(kKey, *callback);

  EXPECT_FALSE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_TRUE(data_.empty());
}

// The storage that always returns stale data.
class StaleStorage : public Storage {
 public:
  StaleStorage() : data_updated_(false) {}
  virtual ~StaleStorage() {}

  // Storage implementation.
  virtual void Get(const std::string& key, const Callback& data_ready) const {
    data_ready(true, key, kStaleWrappedData);
  }

  virtual void Put(const std::string& key, const std::string& value) {
    data_updated_ = true;
  }

  bool data_updated_;

 private:
  DISALLOW_COPY_AND_ASSIGN(StaleStorage);
};

TEST_F(RetrieverTest, UseStaleDataWhenDownloaderFails) {
  // Owned by |resilient_retriver|.
  StaleStorage* stale_storage = new StaleStorage;
  // An empty MockDownloader will fail for any request.
  Retriever resilient_retriever(
      MockDownloader::kMockDataUrl, new MockDownloader, stale_storage);

  scoped_ptr<Retriever::Callback> callback(BuildCallback());
  resilient_retriever.Retrieve(kKey, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_EQ(kStaleData, data_);
  EXPECT_FALSE(stale_storage->data_updated_);
}

TEST_F(RetrieverTest, DoNotUseStaleDataWhenDownloaderSucceeds) {
  // Owned by |resilient_retriver|.
  StaleStorage* stale_storage = new StaleStorage;
  Retriever resilient_retriever(
      FakeDownloader::kFakeDataUrl, new FakeDownloader, stale_storage);

  scoped_ptr<Retriever::Callback> callback(BuildCallback());
  resilient_retriever.Retrieve(kKey, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_FALSE(data_.empty());
  EXPECT_NE(kEmptyData, data_);
  EXPECT_NE(kStaleData, data_);
  EXPECT_TRUE(stale_storage->data_updated_);
}

}  // namespace
