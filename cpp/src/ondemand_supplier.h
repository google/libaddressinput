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

#ifndef I18N_ADDRESSINPUT_ONDEMAND_SUPPLIER_H_
#define I18N_ADDRESSINPUT_ONDEMAND_SUPPLIER_H_

#include <libaddressinput/callback.h>
#include <libaddressinput/supplier.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <map>
#include <set>
#include <string>

#include "retriever.h"

namespace i18n {
namespace addressinput {

class LookupKey;
class Rule;

// An implementation of the Supplier interface that owns a Retriever object,
// through which it loads address metadata as needed, creating Rule objects and
// caching these.
//
// When using an OndemandSupplier, address validation will benefit from address
// metadata server synonym resolution, because the server will be contacted for
// every new LookupKey (ie. every LookupKey that isn't on canonical form and
// isn't already cached).
//
// The maximum size of this cache is naturally limited to the amount of data
// available from the data server. (Currently this is less than 12,000 items of
// in total less than 2 MB of JSON data.)
class OndemandSupplier : public Supplier {
 public:
  // Takes ownership of |retriever|.
  OndemandSupplier(const Retriever* retriever);
  virtual ~OndemandSupplier();

  // Loads the metadata needed for |lookup_key|, then calls |supplied|.
  virtual void Supply(const LookupKey& lookup_key, const Callback& supplied);

  // A RuleHierarchy object encapsulates the set of Rule objects corresponding
  // to a LookupKey, together with methods for retrieving and parsing data as
  // necessary from a Retriever object.
  class RuleHierarchy : public Supplier::RuleHierarchy {
   public:
    RuleHierarchy(const LookupKey& lookup_key,
                  std::map<std::string, const Rule*>* rules,
                  const Callback& supplied);
    virtual ~RuleHierarchy();

    // Adds lookup key string |key| to the queue of data to be retrieved.
    void Queue(const std::string& key);

    // Retrieves and parses data for all queued keys, then calls |supplied_|.
    void Retrieve(const Retriever& retriever);

   private:
    void Load(bool success, const std::string& key, const std::string& data);
    void Loaded();

    std::set<std::string> pending_;
    const LookupKey& lookup_key_;
    std::map<std::string, const Rule*>* const rule_cache_;
    const Callback& supplied_;
    const scoped_ptr<const Retriever::Callback> retrieved_;
    bool success_;

    DISALLOW_COPY_AND_ASSIGN(RuleHierarchy);
  };

 private:
  const scoped_ptr<const Retriever> retriever_;
  std::map<std::string, const Rule*> rule_cache_;

  DISALLOW_COPY_AND_ASSIGN(OndemandSupplier);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_ONDEMAND_SUPPLIER_H_
