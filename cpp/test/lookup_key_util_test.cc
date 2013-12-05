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

#include "lookup_key_util.h"

#include <gtest/gtest.h>

namespace {

using i18n::addressinput::LookupKeyUtil;

TEST(LookupKeyUtilTest, GetUrlForKey) {
  const LookupKeyUtil util("test:///");
  EXPECT_EQ("test:///", util.GetUrlForKey(""));
  EXPECT_EQ("test:///data", util.GetUrlForKey("data"));
  EXPECT_EQ("test:///data/US", util.GetUrlForKey("data/US"));
  EXPECT_EQ("test:///data/CA--fr", util.GetUrlForKey("data/CA--fr"));
}

TEST(LookupKeyUtilTest, GetKeyForUrl) {
  const LookupKeyUtil util("test:///");
  EXPECT_EQ("", util.GetKeyForUrl("test://"));
  EXPECT_EQ("", util.GetKeyForUrl("http://www.google.com/"));
  EXPECT_EQ("", util.GetKeyForUrl(""));
  EXPECT_EQ("", util.GetKeyForUrl("test:///"));
  EXPECT_EQ("data", util.GetKeyForUrl("test:///data"));
  EXPECT_EQ("data/US", util.GetKeyForUrl("test:///data/US"));
  EXPECT_EQ("data/CA--fr", util.GetKeyForUrl("test:///data/CA--fr"));
}

TEST(LookupKeyUtilTest, IsValidationDataUrl) {
  const LookupKeyUtil util("test:///");
  EXPECT_FALSE(util.IsValidationDataUrl("test://"));
  EXPECT_FALSE(util.IsValidationDataUrl("http://www.google.com/"));
  EXPECT_FALSE(util.IsValidationDataUrl(""));
  EXPECT_TRUE(util.IsValidationDataUrl("test:///"));
  EXPECT_TRUE(util.IsValidationDataUrl("test:///data"));
  EXPECT_TRUE(util.IsValidationDataUrl("test:///data/US"));
  EXPECT_TRUE(util.IsValidationDataUrl("test:///data/CA--fr"));
}

}  // namespace
