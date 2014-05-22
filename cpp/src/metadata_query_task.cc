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

#include <libaddressinput/address_data.h>
#include <libaddressinput/address_field.h>
#include <libaddressinput/address_validator.h>

#include <cassert>
#include <cstddef>
#include <string>

#include "lookup_key.h"
#include "metadata_loader.h"

namespace i18n {
namespace addressinput {

MetadataQueryTask::MetadataQueryTask(
    AddressField field,
    const std::string& region_code,
    const AddressValidator::BoolCallback& answered)
    : field_(field),
      region_code_(region_code),
      answered_(answered),
      supplied_(BuildCallback(this, &MetadataQueryTask::ExecuteQuery)),
      lookup_key_(new LookupKey) {
  AddressData address;
  address.region_code = region_code;
  lookup_key_->FromAddress(address);
}

MetadataQueryTask::~MetadataQueryTask() {
}

void MetadataQueryTask::Run(Supplier* supplier) const {
  assert(supplier != NULL);
  supplier->Supply(*lookup_key_, *supplied_);
}

void MetadataQueryTask::ExecuteQuery(
    bool success,
    const LookupKey& lookup_key,
    const Supplier::RuleHierarchy& hierarchy) {
  assert(&lookup_key == lookup_key_.get());  // Sanity check.
  bool answer = false;

  if (success) {
    if (hierarchy.rule_[0] == NULL) {
      success = false;
    } else {
      answer = Query(hierarchy);
    }
  }

  answered_(success, region_code_, answer);
  delete this;
}

}  // namespace addressinput
}  // namespace i18n
