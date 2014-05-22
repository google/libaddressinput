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

#include <libaddressinput/address_validator.h>

#include <libaddressinput/address_field.h>
#include <libaddressinput/supplier.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>

#include "metadata_query_task.h"
#include "ondemand_supplier.h"
#include "retriever.h"
#include "rule.h"
#include "validation_task.h"

namespace i18n {
namespace addressinput {

AddressValidator::AddressValidator(const std::string& validation_data_url,
                                   const Downloader* downloader,
                                   Storage* storage)
    : own_supplier_(new OndemandSupplier(
          new Retriever(validation_data_url, downloader, storage))),
      supplier_(own_supplier_.get()) {
  assert(supplier_ != NULL);
}

AddressValidator::AddressValidator(Supplier* supplier)
    : own_supplier_(),
      supplier_(supplier) {
  assert(supplier_ != NULL);
}

AddressValidator::~AddressValidator() {
}

void AddressValidator::Validate(const AddressData& address,
                                bool allow_postal,
                                bool require_name,
                                const FieldProblemMap* filter,
                                FieldProblemMap* problems,
                                const Callback& validated) const {
  // The ValidationTask object will delete itself after Run() has finished.
  (new ValidationTask(
       address,
       allow_postal,
       require_name,
       filter,
       problems,
       validated))->Run(supplier_);
}

namespace {

class IsFieldRequiredTask : public MetadataQueryTask {
 public:
  IsFieldRequiredTask(AddressField field,
                      const std::string& region_code,
                      const AddressValidator::BoolCallback& answered)
      : MetadataQueryTask(field, region_code, answered) {}

  virtual ~IsFieldRequiredTask() {}

 protected:
  virtual bool Query(const Supplier::RuleHierarchy& hierarchy) const {
    assert(hierarchy.rule_[0] != NULL);
    const Rule& country_rule = *hierarchy.rule_[0];
    return std::find(country_rule.GetRequired().begin(),
                     country_rule.GetRequired().end(),
                     field_) != country_rule.GetRequired().end();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(IsFieldRequiredTask);
};

class IsFieldUsedTask : public MetadataQueryTask {
 public:
  IsFieldUsedTask(AddressField field,
                  const std::string& region_code,
                  const AddressValidator::BoolCallback& answered)
      : MetadataQueryTask(field, region_code, answered) {}

  virtual ~IsFieldUsedTask() {}

 protected:
  virtual bool Query(const Supplier::RuleHierarchy& hierarchy) const {
    assert(hierarchy.rule_[0] != NULL);
    const Rule& country_rule = *hierarchy.rule_[0];
    return std::find(country_rule.GetFormat().begin(),
                     country_rule.GetFormat().end(),
                     FormatElement(field_)) != country_rule.GetFormat().end();
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(IsFieldUsedTask);
};

}  // namespace

void AddressValidator::IsFieldRequired(
    AddressField field,
    const std::string& region_code,
    const BoolCallback& answered) const {
  // The MetadataQueryTask object will delete itself after Run() has finished.
  (new IsFieldRequiredTask(field, region_code, answered))->Run(supplier_);
}

void AddressValidator::IsFieldUsed(
    AddressField field,
    const std::string& region_code,
    const BoolCallback& answered) const {
  // The MetadataQueryTask object will delete itself after Run() has finished.
  (new IsFieldUsedTask(field, region_code, answered))->Run(supplier_);
}

}  // namespace addressinput
}  // namespace i18n
