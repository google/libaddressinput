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

#include "metadata_query_task.h"

#include <libaddressinput/address_field.h>
#include <libaddressinput/address_validator.h>
#include <libaddressinput/callback.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include <gtest/gtest.h>

#include "metadata_loader.h"
#include "rule.h"

namespace i18n {
namespace addressinput {

class LookupKey;

class MetadataQueryTaskTest : public testing::Test {
 private:
  class MockTask : public MetadataQueryTask {
   public:
    MockTask(bool answer,
             const std::string& region_code,
             const AddressValidator::BoolCallback& answered)
        : MetadataQueryTask(
            static_cast<AddressField>(-1),  // The field shouldn't be used.
            region_code,
            answered),
          answer_(answer) {}

    virtual ~MockTask() {}

   protected:
    virtual bool Query(const MetadataLoader::RuleHierarchy& hierarchy) const {
      return answer_;
    }

   private:
    const bool answer_;
    DISALLOW_COPY_AND_ASSIGN(MockTask);
  };

 protected:
  MetadataQueryTaskTest()
      : use_default_rule_(false),
        success_(true),
        region_code_(),
        answer_(),
        called_(false),
        loaded_(BuildCallback(this, &MetadataQueryTaskTest::Loaded)),
        answered_(BuildCallback(this, &MetadataQueryTaskTest::Answered)) {}

  virtual ~MetadataQueryTaskTest() {}

  void Run() {
    std::map<std::string, const Rule*> rules;  // Stub.

    MetadataQueryTask* task = new MockTask(answer_, region_code_, *answered_);

    MetadataLoader::RuleHierarchy* hierarchy =
        new MetadataLoader::RuleHierarchy(*task->lookup_key_, &rules, *loaded_);

    if (use_default_rule_) {
      hierarchy->rule_[0] = &Rule::GetDefault();
    }

    (*task->loaded_)(success_, *task->lookup_key_, *hierarchy);
  }

  bool use_default_rule_;
  bool success_;
  const std::string region_code_;
  bool answer_;
  bool called_;

 private:
  void Loaded(bool, const LookupKey&, const MetadataLoader::RuleHierarchy&) {
    FAIL();  // RuleHierarchy::Retrieve() shouldn't be called in this test.
  }

  void Answered(bool success,
                const std::string& region_code,
                const bool& answer) {
    success_ = success;
    ASSERT_EQ(&region_code_, &region_code);
    answer_ = answer;
    called_ = true;
  }

  const scoped_ptr<const MetadataLoader::Callback> loaded_;  // Stub.
  const scoped_ptr<const AddressValidator::BoolCallback> answered_;

  DISALLOW_COPY_AND_ASSIGN(MetadataQueryTaskTest);
};

namespace {

TEST_F(MetadataQueryTaskTest, FailureCountryRuleNull) {
  success_ = false;

  ASSERT_NO_FATAL_FAILURE(Run());
  ASSERT_TRUE(called_);
  EXPECT_FALSE(success_);
}

TEST_F(MetadataQueryTaskTest, FailureCountryRuleDefault) {
  use_default_rule_ = true;
  success_ = false;

  ASSERT_NO_FATAL_FAILURE(Run());
  ASSERT_TRUE(called_);
  EXPECT_FALSE(success_);
}

TEST_F(MetadataQueryTaskTest, SuccessCountryRuleNull) {
  ASSERT_NO_FATAL_FAILURE(Run());
  ASSERT_TRUE(called_);
  EXPECT_FALSE(success_);
}

TEST_F(MetadataQueryTaskTest, SuccessCountryRuleDefault) {
  use_default_rule_ = true;

  ASSERT_NO_FATAL_FAILURE(Run());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(success_);
  EXPECT_FALSE(answer_);
}

TEST_F(MetadataQueryTaskTest, SuccessCountryRuleDefaultAnswerTrue) {
  use_default_rule_ = true;
  answer_ = true;

  ASSERT_NO_FATAL_FAILURE(Run());
  ASSERT_TRUE(called_);
  EXPECT_TRUE(success_);
  EXPECT_TRUE(answer_);
}

}  // namespace
}  // namespace addressinput
}  // namespace i18n
