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

#include "util/re2ptr.h"  // Must be the first #include statement!

#include "validation_task.h"

#include <libaddressinput/address_data.h>
#include <libaddressinput/address_field.h>
#include <libaddressinput/address_problem.h>
#include <libaddressinput/address_validator.h>
#include <libaddressinput/util/basictypes.h>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "lookup_key.h"
#include "metadata_loader.h"
#include "post_box_matchers.h"
#include "rule.h"

namespace i18n {
namespace addressinput {

ValidationTask::ValidationTask(const AddressData& address,
                               bool allow_postal,
                               bool require_name,
                               const FieldProblemMap* filter,
                               FieldProblemMap* problems,
                               const AddressValidator::Callback& validated)
    : address_(address),
      allow_postal_(allow_postal),
      require_name_(require_name),
      filter_(filter),
      problems_(problems),
      validated_(validated),
      loaded_(BuildCallback(this, &ValidationTask::Validate)),
      lookup_key_(new LookupKey) {
  assert(problems_ != NULL);
  assert(loaded_ != NULL);
  assert(lookup_key_ != NULL);
}

ValidationTask::~ValidationTask() {
}

void ValidationTask::Run(MetadataLoader* metadata) const {
  assert(metadata != NULL);
  problems_->clear();
  lookup_key_->FromAddress(address_);
  metadata->Load(*lookup_key_, *loaded_);
}

void ValidationTask::Validate(bool success,
                              const LookupKey& lookup_key,
                              const MetadataLoader::RuleHierarchy& hierarchy) {
  assert(&lookup_key == lookup_key_.get());  // Sanity check.

  if (success) {
    if (address_.IsFieldEmpty(COUNTRY)) {
      ReportProblemMaybe(COUNTRY, MISSING_REQUIRED_FIELD);
    } else if (hierarchy.rule_[0] == NULL) {
      ReportProblemMaybe(COUNTRY, UNKNOWN_VALUE);
    } else {
      CheckUnexpectedField(hierarchy);
      CheckMissingRequiredField(hierarchy);
      CheckUnknownValue(hierarchy);
      CheckPostalCodeFormatAndValue(hierarchy);
      CheckUsesPoBox(hierarchy);
    }
  }

  validated_(success, address_, *problems_);
  delete this;
}

// A field is UNEXPECTED_FIELD if it is not used in the fmt string in the
// metadata and the current value of that field is not empty.
void ValidationTask::CheckUnexpectedField(
    const MetadataLoader::RuleHierarchy& hierarchy) const {
  assert(hierarchy.rule_[0] != NULL);
  const Rule& country_rule = *hierarchy.rule_[0];

  static const AddressField kFields[] = {
    // COUNTRY is never unexpected.
    ADMIN_AREA,
    LOCALITY,
    DEPENDENT_LOCALITY,
    SORTING_CODE,
    POSTAL_CODE,
    STREET_ADDRESS,
    RECIPIENT
  };

  for (size_t i = 0; i < arraysize(kFields); ++i) {
    AddressField field = kFields[i];
    if (!address_.IsFieldEmpty(field) && IsUnexpected(country_rule, field)) {
      ReportProblemMaybe(field, UNEXPECTED_FIELD);
    }
  }
}

// A field is MISSING_REQUIRED_FIELD if it is listed as a required field in the
// metadata and the current value of that field is empty.
void ValidationTask::CheckMissingRequiredField(
    const MetadataLoader::RuleHierarchy& hierarchy) const {
  assert(hierarchy.rule_[0] != NULL);
  const Rule& country_rule = *hierarchy.rule_[0];

  for (std::vector<AddressField>::const_iterator
       it = country_rule.GetRequired().begin();
       it != country_rule.GetRequired().end(); ++it) {
    if (address_.IsFieldEmpty(*it)) {
      ReportProblemMaybe(*it, MISSING_REQUIRED_FIELD);
    }
  }

  if (require_name_ && address_.IsFieldEmpty(RECIPIENT)) {
    ReportProblemMaybe(RECIPIENT, MISSING_REQUIRED_FIELD);
  }
}

// A field is UNKNOWN_VALUE if the metadata contains a list of possible values
// for the field and the address data server could not match the current value
// of that field to one of those possible values, therefore returning NULL.
void ValidationTask::CheckUnknownValue(
    const MetadataLoader::RuleHierarchy& hierarchy) const {
  for (size_t depth = 1; depth < arraysize(LookupKey::kHierarchy); ++depth) {
    AddressField field = LookupKey::kHierarchy[depth];
    if (!(address_.IsFieldEmpty(field) ||
          hierarchy.rule_[depth - 1] == NULL ||
          hierarchy.rule_[depth - 1]->GetSubKeys().empty() ||
          hierarchy.rule_[depth] != NULL)) {
      ReportProblemMaybe(field, UNKNOWN_VALUE);
    }
  }
}

void ValidationTask::CheckPostalCodeFormatAndValue(
    const MetadataLoader::RuleHierarchy& hierarchy) const {
  assert(hierarchy.rule_[0] != NULL);
  const Rule& country_rule = *hierarchy.rule_[0];

  if (!(ShouldReport(POSTAL_CODE, INVALID_FORMAT) ||
        ShouldReport(POSTAL_CODE, MISMATCHING_VALUE))) {
    return;
  }

  if (address_.IsFieldEmpty(POSTAL_CODE)) {
    return;
  } else if (IsUnexpected(country_rule, POSTAL_CODE)) {
    return;  // Problem already reported by CheckUnexpectedField().
  }

  // Validate general postal code format. A country-level rule specifies the
  // regular expression for the whole postal code.
  const RE2ptr* format_ptr = country_rule.GetPostalCodeMatcher();
  if (format_ptr != NULL &&
      !RE2::FullMatch(address_.postal_code, *format_ptr->ptr) &&
      ShouldReport(POSTAL_CODE, INVALID_FORMAT)) {
    ReportProblem(POSTAL_CODE, INVALID_FORMAT);
    return;
  }

  if (!ShouldReport(POSTAL_CODE, MISMATCHING_VALUE)) {
    return;
  }

  for (size_t depth = arraysize(LookupKey::kHierarchy) - 1;
       depth > 0; --depth) {
    if (hierarchy.rule_[depth] != NULL) {
      // Validate sub-region specific postal code format. A sub-region specifies
      // the regular expression for a prefix of the postal code.
      const RE2ptr* prefix_ptr = hierarchy.rule_[depth]->GetPostalCodeMatcher();
      if (prefix_ptr != NULL) {
        if (!RE2::PartialMatch(address_.postal_code, *prefix_ptr->ptr)) {
          ReportProblem(POSTAL_CODE, MISMATCHING_VALUE);
        }
        return;
      }
    }
  }
}

void ValidationTask::CheckUsesPoBox(
    const MetadataLoader::RuleHierarchy& hierarchy) const {
  assert(hierarchy.rule_[0] != NULL);
  const Rule& country_rule = *hierarchy.rule_[0];

  if (allow_postal_ ||
      !ShouldReport(STREET_ADDRESS, USES_P_O_BOX) ||
      address_.IsFieldEmpty(STREET_ADDRESS)) {
    return;
  }

  std::vector<const RE2ptr*> matchers =
      PostBoxMatchers::GetMatchers(country_rule);
  for (std::vector<std::string>::const_iterator
       line = address_.address_line.begin();
       line != address_.address_line.end(); ++line) {
    for (std::vector<const RE2ptr*>::const_iterator
         matcher = matchers.begin();
         matcher != matchers.end(); ++matcher) {
      if (RE2::PartialMatch(*line, *(*matcher)->ptr)) {
        ReportProblem(STREET_ADDRESS, USES_P_O_BOX);
        return;
      }
    }
  }
}

void ValidationTask::ReportProblem(AddressField field,
                                   AddressProblem problem) const {
  problems_->insert(std::make_pair(field, problem));
}

void ValidationTask::ReportProblemMaybe(AddressField field,
                                        AddressProblem problem) const {
  if (ShouldReport(field, problem)) {
    ReportProblem(field, problem);
  }
}

bool ValidationTask::ShouldReport(AddressField field,
                                  AddressProblem problem) const {
  return filter_ == NULL || filter_->empty() ||
         std::find(filter_->begin(), filter_->end(),
                   FieldProblemMap::value_type(field, problem)) !=
         filter_->end();
}

// static
bool ValidationTask::IsUnexpected(const Rule& rule, AddressField field) {
  // TODO: This and IsFieldUsedTask seem to do the opposite of each other.
  // CheckMissingRequiredField and IsFieldRequired also seem to have duplicated
  // code. We should address this.
  return std::find(rule.GetFormat().begin(), rule.GetFormat().end(),
                   FormatElement(field)) == rule.GetFormat().end();
}

}  // namespace addressinput
}  // namespace i18n
