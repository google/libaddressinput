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
#include <libaddressinput/downloader.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include <gtest/gtest.h>

#include "fake_downloader.h"
#include "fake_storage.h"
#include "region_data_constants.h"

namespace {

using i18n::addressinput::BuildCallback;
using i18n::addressinput::Downloader;
using i18n::addressinput::FakeDownloader;
using i18n::addressinput::FakeStorage;
using i18n::addressinput::RegionDataConstants;
using i18n::addressinput::Retriever;
using i18n::addressinput::scoped_ptr;

const char kKey[] = "data/CA/AB--fr";

// Empty data that the downloader can return.
const char kEmptyData[] = "{}";

// Tests for Retriever object.
class RetrieverTest : public testing::Test {
 protected:
  RetrieverTest()
      : retriever_(FakeDownloader::kFakeDataUrl,
                   new FakeDownloader,
                   new FakeStorage),
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

// The downloader that always fails.
class FaultyDownloader : public Downloader {
 public:
  FaultyDownloader() {}
  virtual ~FaultyDownloader() {}

  // Downloader implementation.
  virtual void Download(const std::string& url,
                        const Callback& downloaded) const {
    downloaded(false, url, "garbage");
  }
};

TEST_F(RetrieverTest, FaultyDownloader) {
  Retriever bad_retriever(FakeDownloader::kFakeDataUrl,
                          new FaultyDownloader,
                          new FakeStorage);

  scoped_ptr<Retriever::Callback> callback(BuildCallback());
  bad_retriever.Retrieve(kKey, *callback);

  EXPECT_FALSE(success_);
  EXPECT_EQ(kKey, key_);
  EXPECT_TRUE(data_.empty());
}

}  // namespace
