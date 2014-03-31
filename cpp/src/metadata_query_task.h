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

#ifndef I18N_ADDRESSINPUT_METADATA_QUERY_TASK_H_
#define I18N_ADDRESSINPUT_METADATA_QUERY_TASK_H_

#include <libaddressinput/address_field.h>
#include <libaddressinput/address_validator.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

#include "metadata_loader.h"

namespace i18n {
namespace addressinput {

class LookupKey;

// A MetadataQueryTask object encapsulates the information necessary to perform
// the checking for an Is*() method that answers a yes/no question and call a
// callback when that has been done. Calling the Run() method will load required
// metadata, then perform checking, call the callback and delete the
// MetadataQueryTask object itself.
//
// The logic of the different Is*() methods is implemented by the virtual
// Query() method of subclasses of the abstract MetadataQueryTask base class.
class MetadataQueryTask {
 public:
  MetadataQueryTask(AddressField field,
                    const std::string& region_code,
                    const AddressValidator::BoolCallback& answered);

  virtual ~MetadataQueryTask();

  // Calls metadata->Load(), with ExecuteQuery() as callback.
  void Run(MetadataLoader* metadata) const;

 protected:
  // Uses the address metadata of |hierarchy| to answer a yes/no question.
  virtual bool Query(const MetadataLoader::RuleHierarchy& hierarchy) const = 0;

  const AddressField field_;

 private:
  friend class MetadataQueryTaskTest;

  // Executes Query(), if |success| is true and |hierarchy| contains data. Then
  // calls the |answered_| callback and deletes this MetadataQueryTask object.
  void ExecuteQuery(bool success,
                    const LookupKey& lookup_key,
                    const MetadataLoader::RuleHierarchy& hierarchy);

  const std::string& region_code_;
  const AddressValidator::BoolCallback& answered_;
  const scoped_ptr<const MetadataLoader::Callback> loaded_;
  const scoped_ptr<LookupKey> lookup_key_;

  DISALLOW_COPY_AND_ASSIGN(MetadataQueryTask);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_METADATA_QUERY_TASK_H_
