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

#include "util/string_compare.h"

#include <string>

#include <gtest/gtest.h>

namespace {

using i18n::addressinput::StringCompare;

struct TestCase {
  TestCase(const std::string& left,
           const std::string& right,
           bool should_be_equal)
      : left(left), right(right), should_be_equal(should_be_equal) {}

  ~TestCase() {}

  std::string left;
  std::string right;
  bool should_be_equal;
};

class StringCompareTest : public testing::TestWithParam<TestCase> {
 protected:
  StringCompare compare_;
};

TEST_P(StringCompareTest, CorrectComparison) {
  if (GetParam().should_be_equal) {
    EXPECT_TRUE(compare_.NaturalEquals(GetParam().left, GetParam().right));
  } else {
    EXPECT_FALSE(compare_.NaturalEquals(GetParam().left, GetParam().right));
  }
}

INSTANTIATE_TEST_CASE_P(
    Comparisons, StringCompareTest,
    testing::Values(TestCase("foo", "foo", true),
                    TestCase("foo", "FOO", true),
                    TestCase("bar", "foo", false),
                    TestCase("강원도", "강원도", true),
                    TestCase("강원도", "대구광역시", false),
                    TestCase("ZÜRICH", "zürich", true)));

}  // namespace
