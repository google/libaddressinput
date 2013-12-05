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

#include "fake_downloader.h"

#include <libaddressinput/callback.h>
#include <libaddressinput/downloader.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include <gtest/gtest.h>

#include "region_data_constants.h"

namespace {

using i18n::addressinput::BuildCallback;
using i18n::addressinput::Downloader;
using i18n::addressinput::FakeDownloader;
using i18n::addressinput::RegionDataConstants;
using i18n::addressinput::scoped_ptr;

// Tests for FakeDownloader object.
class FakeDownloaderTest : public testing::TestWithParam<std::string> {
 protected:
  FakeDownloaderTest() : downloader_(), success_(false), url_(), data_() {}
  virtual ~FakeDownloaderTest() {}

  Downloader::Callback* BuildCallback() {
    return ::BuildCallback(this, &FakeDownloaderTest::OnDownloaded);
  }

  FakeDownloader downloader_;
  bool success_;
  std::string url_;
  std::string data_;

 private:
  void OnDownloaded(bool success,
                    const std::string& url,
                    const std::string& data) {
    success_ = success;
    url_ = url;
    data_ = data;
  }
};

// Returns testing::AssertionSuccess if |data| is valid downloaded data for
// |key|.
testing::AssertionResult DataIsValid(const std::string& data,
                                     const std::string& key) {
  if (data.empty()) {
    return testing::AssertionFailure() << "empty data";
  }

  std::string expected_data_begin = "{\"id\":\"" + key + "\"";
  if (data.compare(0, expected_data_begin.length(), expected_data_begin) != 0) {
    return testing::AssertionFailure() << data << " does not begin with "
                                       << expected_data_begin;
  }

  static const char kDataEnd[] = "\"}";
  static const size_t kDataEndLength = sizeof kDataEnd - 1;
  if (data.compare(data.length() - kDataEndLength,
                   kDataEndLength,
                   kDataEnd,
                   kDataEndLength) != 0) {
    return testing::AssertionFailure() << data << " does not end with "
                                       << kDataEnd;
  }

  return testing::AssertionSuccess();
}

// Verifies that FakeDownloader downloads valid data for a region code.
TEST_P(FakeDownloaderTest, FakeDownloaderHasValidDataForRegion) {
  std::string key = "data/" + GetParam();
  std::string url = std::string(FakeDownloader::kFakeDataUrl) + key;
  scoped_ptr<Downloader::Callback> callback(BuildCallback());
  downloader_.Download(url, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(url, url_);
  EXPECT_TRUE(DataIsValid(data_, key));
};

// Test all region codes.
INSTANTIATE_TEST_CASE_P(
    AllRegions, FakeDownloaderTest,
    testing::ValuesIn(RegionDataConstants::GetRegionCodes()));

// Verifies that the key "data" also contains valid data.
TEST_F(FakeDownloaderTest, DownloadExistingData) {
  static const std::string kKey = "data";
  static const std::string kUrl =
      std::string(FakeDownloader::kFakeDataUrl) + kKey;
  scoped_ptr<Downloader::Callback> callback(BuildCallback());
  downloader_.Download(kUrl, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kUrl, url_);
  EXPECT_TRUE(DataIsValid(data_, kKey));
}

// Verifies that downloading a missing key will return "{}".
TEST_F(FakeDownloaderTest, DownloadMissingKeyReturnsEmptyDictionary) {
  static const std::string kJunkUrl =
      std::string(FakeDownloader::kFakeDataUrl) + "junk";
  scoped_ptr<Downloader::Callback> callback(BuildCallback());
  downloader_.Download(kJunkUrl, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kJunkUrl, url_);
  EXPECT_EQ("{}", data_);
}

// Verifies that downloading an empty key will return "{}".
TEST_F(FakeDownloaderTest, DownloadEmptyKeyReturnsEmptyDictionary) {
  static const std::string kPrefixOnlyUrl = FakeDownloader::kFakeDataUrl;
  scoped_ptr<Downloader::Callback> callback(BuildCallback());
  downloader_.Download(kPrefixOnlyUrl, *callback);

  EXPECT_TRUE(success_);
  EXPECT_EQ(kPrefixOnlyUrl, url_);
  EXPECT_EQ("{}", data_);
}

// Verifies that downloading a real URL fails.
TEST_F(FakeDownloaderTest, DownloadRealUrlFals) {
  static const std::string kRealUrl = "http://www.google.com/";
  scoped_ptr<Downloader::Callback> callback(BuildCallback());
  downloader_.Download(kRealUrl, *callback);

  EXPECT_FALSE(success_);
  EXPECT_EQ(kRealUrl, url_);
  EXPECT_TRUE(data_.empty());
}

}  // namespace
