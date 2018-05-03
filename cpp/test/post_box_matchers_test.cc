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

#include "post_box_matchers.h"

#include <gtest/gtest.h>

#include "rule.h"

namespace {

using i18n::addressinput::PostBoxMatchers;
using i18n::addressinput::Rule;

TEST(PostBoxMatchersTest, AlwaysGetMatcherForLanguageUnd) {
  Rule rule;
  const auto& matchers = PostBoxMatchers::GetMatchers(rule);
  EXPECT_EQ(1, matchers.size());
  EXPECT_TRUE(matchers[0] != nullptr);
}

TEST(PostBoxMatchersTest, NoMatcherForInvalidLanguage) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{\"languages\":\"xx\"}"));
  const auto& matchers = PostBoxMatchers::GetMatchers(rule);
  EXPECT_EQ(1, matchers.size());
  EXPECT_TRUE(matchers[0] != nullptr);
}

TEST(PostBoxMatchersTest, HasMatcherForValidLanguage) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{\"languages\":\"sv\"}"));
  const auto& matchers = PostBoxMatchers::GetMatchers(rule);
  EXPECT_EQ(2, matchers.size());
  EXPECT_TRUE(matchers[0] != nullptr);
  EXPECT_TRUE(matchers[1] != nullptr);
}

TEST(PostBoxMatchersTest, MixValidAndInvalidLanguage) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{\"languages\":\"xx~sv\"}"));
  const auto& matchers = PostBoxMatchers::GetMatchers(rule);
  EXPECT_EQ(2, matchers.size());
  EXPECT_TRUE(matchers[0] != nullptr);
  EXPECT_TRUE(matchers[1] != nullptr);
}

TEST(PostBoxMatchersTest, UseBaseLanguageForMatching) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{\"languages\":\"sv-SE\"}"));
  const auto& matchers = PostBoxMatchers::GetMatchers(rule);
  EXPECT_EQ(2, matchers.size());
  EXPECT_TRUE(matchers[0] != nullptr);
  EXPECT_TRUE(matchers[1] != nullptr);
}

TEST(PostBoxMatchersTest, LenientLanguageTagParsing) {
  Rule rule;
  ASSERT_TRUE(rule.ParseSerializedRule("{\"languages\":\"SV_SE\"}"));
  const auto& matchers = PostBoxMatchers::GetMatchers(rule);
  EXPECT_EQ(2, matchers.size());
  EXPECT_TRUE(matchers[0] != nullptr);
  EXPECT_TRUE(matchers[1] != nullptr);
}

}  // namespace
