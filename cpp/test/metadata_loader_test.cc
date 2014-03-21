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

#include "metadata_loader.h"

#include <libaddressinput/address_data.h>
#include <libaddressinput/callback.h>
#include <libaddressinput/downloader.h>
#include <libaddressinput/null_storage.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <cstddef>
#include <map>
#include <string>
#include <utility>

#include <gtest/gtest.h>

#include "fake_downloader.h"
#include "lookup_key.h"
#include "retriever.h"
#include "rule.h"

namespace {

// For compatibility with legacy compilers, that can't handle UTF-8 string
// literals in source code (please let them disappear from common use soon),
// Chinese strings required in the test code are here provided as string
// constants in hex escaped UTF-8 encoding.

/* "九龍" */
const char kKowloon[] = "\xE4\xB9\x9D\xE9\xBE\x8D";

/* "新疆" */
const char kXinJiang[] = "\xE6\x96\xB0\xE7\x96\x86";

/* "喀什地区" */
const char kKashiDiqu[] = "\xE5\x96\x80\xE4\xBB\x80\xE5\x9C\xB0\xE5\x8C\xBA";

/* "喀什市" */
const char kKashiShi[] = "\xE5\x96\x80\xE4\xBB\x80\xE5\xB8\x82";

using i18n::addressinput::AddressData;
using i18n::addressinput::BuildCallback;
using i18n::addressinput::Downloader;
using i18n::addressinput::FakeDownloader;
using i18n::addressinput::LookupKey;
using i18n::addressinput::MetadataLoader;
using i18n::addressinput::NullStorage;
using i18n::addressinput::Retriever;
using i18n::addressinput::Rule;
using i18n::addressinput::scoped_ptr;

class MetadataLoaderTest : public testing::Test {
 protected:
  MetadataLoaderTest()
      : address_(),
        hierarchy_(),
        called_(false),
        lookup_key_(),
        loader_(
            new Retriever(FakeDownloader::kFakeDataUrl,
                          new FakeDownloader,
                          new NullStorage)),
        loaded_(BuildCallback(this, &MetadataLoaderTest::Loaded)) {}

  virtual ~MetadataLoaderTest() {}

  void Load() {
    lookup_key_.FromAddress(address_);
    loader_.Load(lookup_key_, *loaded_);
  }

  AddressData address_;
  scoped_ptr<const MetadataLoader::RuleHierarchy> hierarchy_;
  bool called_;

 private:
  void Loaded(bool success,
              const LookupKey& lookup_key,
              const MetadataLoader::RuleHierarchy& hierarchy) {
    ASSERT_TRUE(success);
    ASSERT_EQ(&lookup_key_, &lookup_key);
    hierarchy_.reset(&hierarchy);
    called_ = true;
  }

  LookupKey lookup_key_;
  MetadataLoader loader_;
  const scoped_ptr<const MetadataLoader::Callback> loaded_;

  DISALLOW_COPY_AND_ASSIGN(MetadataLoaderTest);
};

TEST_F(MetadataLoaderTest, Invalid) {
  address_.region_code = "QZ";

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(MetadataLoaderTest, Valid) {
  address_.region_code = "SE";

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
  EXPECT_EQ("data/SE", hierarchy_->rule_[0]->GetId());
  EXPECT_FALSE(hierarchy_->rule_[0]->GetRequired().empty());
  EXPECT_FALSE(hierarchy_->rule_[0]->GetFormat().empty());
  EXPECT_TRUE(hierarchy_->rule_[0]->GetPostalCodeMatcher() != NULL);
}

TEST_F(MetadataLoaderTest, KeyDepthEqualsMaxDepth) {
  address_.region_code = "HK";
  address_.administrative_area = kKowloon;

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(MetadataLoaderTest, KeyDepthLargerThanMaxDepth) {
  address_.region_code = "HK";
  address_.administrative_area = kKowloon;
  address_.locality = "bbb";  // Ignored!

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(MetadataLoaderTest, KeyDepthSmallerThanMaxDepth) {
  address_.region_code = "HK";

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(MetadataLoaderTest, KeyDepth0) {
  address_.region_code = "CN";

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(MetadataLoaderTest, KeyDepth1) {
  address_.region_code = "CN";
  address_.administrative_area = kXinJiang;

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(MetadataLoaderTest, KeyDepth2) {
  address_.region_code = "CN";
  address_.administrative_area = kXinJiang;
  address_.locality = kKashiDiqu;

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(MetadataLoaderTest, KeyDepth3) {
  address_.region_code = "CN";
  address_.administrative_area = kXinJiang;
  address_.locality = kKashiDiqu;
  address_.dependent_locality = kKashiShi;

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] != NULL);
}

TEST_F(MetadataLoaderTest, RuleCache) {
  address_.region_code = "US";
  address_.administrative_area = "CA";

  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);

  // Keep a pointer to the current RuleHierarchy object and then verify that
  // calling Load() again with the same LookupKey returns a new RuleHierarchy
  // object which points to the same Rule objects stored in the MetadataLoader
  // cache as the old RuleHierarchy object pointed to.

  const scoped_ptr<const MetadataLoader::RuleHierarchy> hierarchy(
      hierarchy_.release());

  called_ = false;
  ASSERT_NO_FATAL_FAILURE(Load());
  ASSERT_TRUE(called_);
  EXPECT_NE(hierarchy.get(), hierarchy_.get());
  EXPECT_EQ(hierarchy->rule_[0], hierarchy_->rule_[0]);
  EXPECT_EQ(hierarchy->rule_[1], hierarchy_->rule_[1]);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

class RuleHierarchyTest : public testing::Test {
 protected:
  class MockDownloader : public Downloader {
   public:
    static const char kMockDataUrl[];
    static const size_t kMockDataUrlLength;

    MockDownloader() {}
    virtual ~MockDownloader() {}

    virtual void Download(const std::string& url,
                          const Callback& downloaded) const {
      ASSERT_EQ(0, url.compare(0, kMockDataUrlLength, kMockDataUrl));
      std::string key(url, kMockDataUrlLength);
      std::map<std::string, std::string>::const_iterator it = data_.find(key);
      bool success = it != data_.end();
      downloaded(success, url, success ? it->second : std::string());
    }

    std::map<std::string, std::string> data_;

   private:
    DISALLOW_COPY_AND_ASSIGN(MockDownloader);
  };

  MockDownloader* const downloader_;

 private:
  std::map<std::string, const Rule*> rule_cache_;
  const scoped_ptr<Retriever> retriever_;
  const scoped_ptr<const MetadataLoader::Callback> loaded_;

 protected:
  RuleHierarchyTest()
      : downloader_(new MockDownloader),
        rule_cache_(),
        retriever_(
            new Retriever(
                MockDownloader::kMockDataUrl, downloader_, new NullStorage)),
        loaded_(BuildCallback(this, &RuleHierarchyTest::Loaded)),
        success_(true),
        lookup_key_(),
        hierarchy_(
            new MetadataLoader::RuleHierarchy(
                lookup_key_, &rule_cache_, *loaded_)),
        called_(false) {}

  virtual ~RuleHierarchyTest() {
    for (std::map<std::string, const Rule*>::const_iterator
         it = rule_cache_.begin(); it != rule_cache_.end(); ++it) {
      delete it->second;
    }
  }

  void Retrieve() {
    hierarchy_->Retrieve(*retriever_);
  }

  bool success_;  // Expected status from MockDownloader.
  LookupKey lookup_key_;  // Stub.
  const scoped_ptr<MetadataLoader::RuleHierarchy> hierarchy_;
  bool called_;

 private:
  void Loaded(bool success,
              const LookupKey& lookup_key,
              const MetadataLoader::RuleHierarchy& hierarchy) {
    ASSERT_EQ(success_, success);
    ASSERT_EQ(&lookup_key_, &lookup_key);
    ASSERT_EQ(hierarchy_.get(), &hierarchy);
    called_ = true;
  }

  DISALLOW_COPY_AND_ASSIGN(RuleHierarchyTest);
};

const char RuleHierarchyTest::MockDownloader::kMockDataUrl[] = "mock:///";

const size_t RuleHierarchyTest::MockDownloader::kMockDataUrlLength =
    sizeof RuleHierarchyTest::MockDownloader::kMockDataUrl - 1;

TEST_F(RuleHierarchyTest, Empty) {
  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);
}

TEST_F(RuleHierarchyTest, Invalid) {
  hierarchy_->Queue("data/XA");

  success_ = false;

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
}

TEST_F(RuleHierarchyTest, Valid) {
  downloader_->data_.insert(std::make_pair("data/XA", "{\"id\":\"data/XA\"}"));

  hierarchy_->Queue("data/XA");

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);

  EXPECT_EQ("data/XA", hierarchy_->rule_[0]->GetId());

  // All rules on the COUNTRY level inherit from the default rule.
  EXPECT_FALSE(hierarchy_->rule_[0]->GetFormat().empty());
  EXPECT_FALSE(hierarchy_->rule_[0]->GetRequired().empty());
  EXPECT_TRUE(hierarchy_->rule_[0]->GetPostalCodeMatcher() == NULL);
}

TEST_F(RuleHierarchyTest, ValidHierarchy) {
  downloader_->data_.insert(
      std::make_pair("data/XA", "{\"id\":\"data/XA\"}"));
  downloader_->data_.insert(
      std::make_pair("data/XA/aa", "{\"id\":\"data/XA/aa\"}"));
  downloader_->data_.insert(
      std::make_pair("data/XA/aa/bb", "{\"id\":\"data/XA/aa/bb\"}"));
  downloader_->data_.insert(
      std::make_pair("data/XA/aa/bb/cc", "{\"id\":\"data/XA/aa/bb/cc\"}"));

  hierarchy_->Queue("data/XA");
  hierarchy_->Queue("data/XA/aa");
  hierarchy_->Queue("data/XA/aa/bb");
  hierarchy_->Queue("data/XA/aa/bb/cc");

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] != NULL);

  EXPECT_EQ("data/XA", hierarchy_->rule_[0]->GetId());
  EXPECT_EQ("data/XA/aa", hierarchy_->rule_[1]->GetId());
  EXPECT_EQ("data/XA/aa/bb", hierarchy_->rule_[2]->GetId());
  EXPECT_EQ("data/XA/aa/bb/cc", hierarchy_->rule_[3]->GetId());

  // All rules on the COUNTRY level inherit from the default rule.
  EXPECT_FALSE(hierarchy_->rule_[0]->GetFormat().empty());
  EXPECT_FALSE(hierarchy_->rule_[0]->GetRequired().empty());

  // Only rules on the COUNTRY level inherit from the default rule.
  EXPECT_TRUE(hierarchy_->rule_[1]->GetFormat().empty());
  EXPECT_TRUE(hierarchy_->rule_[1]->GetRequired().empty());
  EXPECT_TRUE(hierarchy_->rule_[2]->GetFormat().empty());
  EXPECT_TRUE(hierarchy_->rule_[2]->GetRequired().empty());
  EXPECT_TRUE(hierarchy_->rule_[3]->GetFormat().empty());
  EXPECT_TRUE(hierarchy_->rule_[3]->GetRequired().empty());
}

TEST_F(RuleHierarchyTest, Alias) {
  downloader_->data_.insert(
      std::make_pair("data/XA", "{\"id\":\"data/XA\"}"));
  downloader_->data_.insert(
      std::make_pair("data/XA/aa", "{\"id\":\"data/XA/aa\"}"));
  downloader_->data_.insert(
      std::make_pair("data/XA/alias", "{\"id\":\"data/XA/aa\"}"));

  hierarchy_->Queue("data/XA");
  hierarchy_->Queue("data/XA/aa");

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);

  EXPECT_EQ("data/XA", hierarchy_->rule_[0]->GetId());
  EXPECT_EQ("data/XA/aa", hierarchy_->rule_[1]->GetId());

  // Keep pointers to the existing Rule objects but overwrite the pointers in
  // RuleHierarchy and then verify that calling Retrieve() again with idential
  // or aliased keys returns pointers to the existing objects.

  const Rule* const rule0 = hierarchy_->rule_[0];
  const Rule* const rule1 = hierarchy_->rule_[1];

  hierarchy_->rule_[0] = NULL;
  hierarchy_->rule_[1] = NULL;

  hierarchy_->Queue("data/XA");
  hierarchy_->Queue("data/XA/alias");

  called_ = false;
  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);

  EXPECT_EQ("data/XA", hierarchy_->rule_[0]->GetId());
  EXPECT_EQ("data/XA/aa", hierarchy_->rule_[1]->GetId());

  EXPECT_EQ(rule0, hierarchy_->rule_[0]);
  EXPECT_EQ(rule1, hierarchy_->rule_[1]);
}

TEST_F(RuleHierarchyTest, InvalidJson1) {
  downloader_->data_.insert(std::make_pair("data/XA", ":"));

  success_ = false;

  hierarchy_->Queue("data/XA");

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
}

TEST_F(RuleHierarchyTest, InvalidJson2) {
  downloader_->data_.insert(std::make_pair("data/XA", "{\"id\":\"data/XA\"}"));
  downloader_->data_.insert(std::make_pair("data/XA/aa", ":"));

  success_ = false;

  hierarchy_->Queue("data/XA");
  hierarchy_->Queue("data/XA/aa");

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
}

TEST_F(RuleHierarchyTest, EmptyJsonJustMeansServerKnowsNothingAboutKey) {
  downloader_->data_.insert(std::make_pair("data/XA", "{\"id\":\"data/XA\"}"));
  downloader_->data_.insert(std::make_pair("data/XA/aa", "{}"));

  hierarchy_->Queue("data/XA");
  hierarchy_->Queue("data/XA/aa");

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(hierarchy_->rule_[0] != NULL);
  EXPECT_TRUE(hierarchy_->rule_[1] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[2] == NULL);
  EXPECT_TRUE(hierarchy_->rule_[3] == NULL);

  EXPECT_EQ("data/XA", hierarchy_->rule_[0]->GetId());
}

TEST_F(RuleHierarchyTest, IfCountryFailsAllFails) {
  downloader_->data_.insert(
      std::make_pair("data/XA/aa", "{\"id\":\"data/XA/aa\"}"));

  success_ = false;

  hierarchy_->Queue("data/XA");
  hierarchy_->Queue("data/XA/aa");

  ASSERT_NO_FATAL_FAILURE(Retrieve());
  ASSERT_TRUE(called_);
}

}  // namespace
