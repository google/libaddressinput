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
#include <libaddressinput/ondemand_supplier.h>
#include <libaddressinput/supplier.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include "retriever.h"
#include "validation_task.h"

namespace i18n {
namespace addressinput {

AddressValidator::AddressValidator(const std::string& validation_data_url,
                                   const Downloader* downloader,
                                   Storage* storage)
    : own_supplier_(
          new OndemandSupplier(validation_data_url, downloader, storage)),
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

}  // namespace addressinput
}  // namespace i18n
