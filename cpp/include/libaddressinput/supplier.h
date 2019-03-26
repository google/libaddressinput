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

#ifndef I18N_ADDRESSINPUT_SUPPLIER_H_
#define I18N_ADDRESSINPUT_SUPPLIER_H_

#include <libaddressinput/callback.h>
#include <string>

namespace i18n {
namespace addressinput {

class LookupKey;
class Rule;

// Interface for objects that are able to supply the AddressValidator with the
// metadata needed to validate an address, as described by a LookupKey.
class Supplier {
 public:
  struct RuleHierarchy;
  using Callback =
      i18n::addressinput::Callback<const LookupKey&, const RuleHierarchy&>;

  virtual ~Supplier() = default;

  // Aggregates the metadata needed for |lookup_key| into a RuleHierarchy
  // object, then calls |supplied|. Implementations of this interface may
  // either load the necessary data on demand, or fail if the necessary data
  // hasn't already been loaded.
  virtual void Supply(const LookupKey& lookup_key,
                      const Callback& supplied) = 0;

  // Aggregates the metadata (in all available languages) needed for
  // |lookup_key| into a RuleHierarchy object, then calls |supplied|.
  // Implementations of this interface may either load the necessary data on
  // demand, or fail if the necessary data hasn't already been loaded.
  virtual void SupplyGlobally(const LookupKey& lookup_key,
                              const Callback& supplied) = 0;

  // Looking at the metadata, returns the depths of the available rules for the
  // region code. For example, if for a certain |region_code|, |rule_index_| has
  // the list of values for admin area and city, but not for the dependent
  // locality the depth would be 3.
  virtual size_t GetLoadedRuleDepth(const std::string& region_code) const {
    return 0;
  }

  // A RuleHierarchy object encapsulates the hierarchical list of Rule objects
  // that corresponds to a particular LookupKey.
  struct RuleHierarchy {
    RuleHierarchy() : rule() {}
    const Rule* rule[4];  // Cf. LookupKey::kHierarchy.
  };
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_SUPPLIER_H_
