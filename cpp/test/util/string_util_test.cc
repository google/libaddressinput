// Copyright (C) 2014 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

#include "util/string_util.h"

#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace {

using i18n::addressinput::DoReplaceStringPlaceholders;

TEST(StringUtilTest, Ok) {
  std::vector<std::string> subst;
  subst.emplace_back("A");
  subst.emplace_back("B");
  subst.emplace_back("C");

  EXPECT_EQ("aA,bB,cC", DoReplaceStringPlaceholders("a$1,b$2,c$3", subst));
}

TEST(StringUtilTest, FewParameters) {
  std::vector<std::string> subst;
  subst.emplace_back("A");
  subst.emplace_back("B");
  subst.emplace_back("C");

  EXPECT_EQ("aA,bB,cC,d,aA",
            DoReplaceStringPlaceholders("a$1,b$2,c$3,d$4,a$1", subst));
}

TEST(StringUtilTest, MoreThan9Parameters) {
  std::vector<std::string> subst;
  subst.emplace_back("A");
  subst.emplace_back("B");
  subst.emplace_back("C");
  subst.emplace_back("D");
  subst.emplace_back("E");
  subst.emplace_back("F");
  subst.emplace_back("G");
  subst.emplace_back("H");
  subst.emplace_back("I");
  subst.emplace_back("J");
  subst.emplace_back("K");

  EXPECT_EQ("aA,bB,cC,dD,eE,fF,gG,hH,iI,jJ,kK,aA",
            DoReplaceStringPlaceholders("a$1,b$2,c$3,d$4,e$5,f$6,g$7,h$8,i$9,"
                                        "j$10,k$11,a$1",
                                        subst));
}

TEST(StringUtilTest, ConsecutiveDollarSigns) {
  std::vector<std::string> subst;
  subst.emplace_back("A");
  subst.emplace_back("B");
  subst.emplace_back("C");

  EXPECT_EQ("$1 $$2 $$$3",
            DoReplaceStringPlaceholders("$$1 $$$2 $$$$3", subst));
}

}  // namespace
