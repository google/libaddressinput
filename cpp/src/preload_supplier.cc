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

#include <libaddressinput/preload_supplier.h>

#include <libaddressinput/address_data.h>
#include <libaddressinput/address_field.h>
#include <libaddressinput/callback.h>
#include <libaddressinput/supplier.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "language.h"
#include "lookup_key.h"
#include "region_data_constants.h"
#include "retriever.h"
#include "rule.h"
#include "util/json.h"
#include "util/string_compare.h"

namespace i18n {
namespace addressinput {

namespace {

// STL predicate less<> that uses StringCompare to match strings that a human
// reader would consider to be "the same". The default implementation just does
// case insensitive string comparison, but StringCompare can be overriden with
// more sophisticated implementations.
class IndexLess : public std::binary_function<std::string, std::string, bool> {
 public:
  result_type operator()(const first_argument_type& a,
                         const second_argument_type& b) const {
    return kStringCompare.NaturalLess(a, b);
  }

 private:
  static const StringCompare kStringCompare;
};

const StringCompare IndexLess::kStringCompare;

}  // namespace

class IndexMap : public std::map<std::string, const Rule*, IndexLess> {};

namespace {

class Helper {
 public:
  // Does not take ownership of its parameters.
  Helper(const std::string& region_code,
         const std::string& key,
         const PreloadSupplier::Callback& loaded,
         const Retriever& retriever,
         std::set<std::string>* pending,
         IndexMap* rule_index,
         std::vector<const Rule*>* rule_storage)
      : region_code_(region_code),
        loaded_(loaded),
        pending_(pending),
        rule_index_(rule_index),
        rule_storage_(rule_storage),
        retrieved_(BuildCallback(this, &Helper::OnRetrieved)) {
    assert(pending_ != NULL);
    assert(rule_index_ != NULL);
    assert(rule_storage_ != NULL);
    assert(retrieved_ != NULL);
    pending_->insert(key);
    retriever.Retrieve(key, *retrieved_);
  }

 private:
  ~Helper() {}

  void OnRetrieved(bool success,
                   const std::string& key,
                   const std::string& data) {
    int rule_count = 0;

    size_t status = pending_->erase(key);
    assert(status == 1);  // There will always be one item erased from the set.
    (void)status;  // Prevent unused variable if assert() is optimized away.

    Json json;
    std::vector<const Rule*> sub_rules;

    if (!success) {
      goto callback;
    }

    if (!json.ParseObject(data)) {
      success = false;
      goto callback;
    }

    for (std::vector<std::string>::const_iterator
         it = json.GetKeys().begin(); it != json.GetKeys().end(); ++it) {
      if (!json.HasDictionaryValueForKey(*it)) {
        success = false;
        goto callback;
      }
      const Json& value = json.GetDictionaryValueForKey(*it);

      if (!value.HasStringValueForKey("id")) {
        success = false;
        goto callback;
      }
      const std::string& id = value.GetStringValueForKey("id");
      assert(*it == id);  // Sanity check.

      size_t depth = std::count(id.begin(), id.end(), '/') - 1;
      assert(depth < arraysize(LookupKey::kHierarchy));
      AddressField field = LookupKey::kHierarchy[depth];

      Rule* rule = new Rule;
      if (field == COUNTRY) {
        // All rules on the COUNTRY level inherit from the default rule.
        rule->CopyFrom(Rule::GetDefault());
      }
      rule->ParseJsonRule(value);
      assert(id == rule->GetId());  // Sanity check.

      rule_storage_->push_back(rule);
      if (depth > 0) {
        sub_rules.push_back(rule);
      }

      // Add the ID of this Rule object to the rule index.
      std::pair<std::map<std::string, const Rule*>::iterator, bool> result =
          rule_index_->insert(std::make_pair(id, rule));
      assert(result.second);
      (void)result;  // Prevent unused variable if assert() is optimized away.

      ++rule_count;
    }

    /*
     * Normally the address metadata server takes care of mapping from natural
     * language names to metadata IDs (eg. "São Paulo" -> "SP") and from Latin
     * script names to local script names (eg. "Tokushima" -> "徳島県").
     *
     * As the PreloadSupplier doesn't contact the metadata server upon each
     * Supply() request, it instead has an internal lookup table (rule_index_)
     * that contains such mappings.
     *
     * This lookup table is populated by iterating over all sub rules and for
     * each of them construct ID strings using human readable names (eg. "São
     * Paulo") and using Latin script names (eg. "Tokushima").
     */
    for (std::vector<const Rule*>::const_iterator
         it = sub_rules.begin(); it != sub_rules.end(); ++it) {
      std::stack<const Rule*> hierarchy;
      hierarchy.push(*it);

      // Push pointers to all parent Rule objects onto the hierarchy stack.
      for (std::string parent_id((*it)->GetId());;) {
        // Strip the last part of parent_id. Break if COUNTRY level is reached.
        std::string::size_type pos = parent_id.rfind('/');
        if (pos == sizeof "data/ZZ" - 1) {
          break;
        }
        parent_id.resize(pos);

        std::map<std::string, const Rule*>::const_iterator jt =
            rule_index_->find(parent_id);
        assert(jt != rule_index_->end());
        hierarchy.push(jt->second);
      }

      std::string human_id((*it)->GetId().substr(0, sizeof "data/ZZ" - 1));
      std::string latin_id(human_id);

      // Append the names from all Rule objects on the hierarchy stack.
      for (; !hierarchy.empty(); hierarchy.pop()) {
        const Rule* rule = hierarchy.top();

        human_id.push_back('/');
        if (!rule->GetName().empty()) {
          human_id.append(rule->GetName());
        } else {
          // If the "name" field is empty, the name is the last part of the ID.
          const std::string& id = rule->GetId();
          std::string::size_type pos = id.rfind('/');
          assert(pos != std::string::npos);
          human_id.append(id.substr(pos + 1));
        }

        if (!rule->GetLatinName().empty()) {
          latin_id.push_back('/');
          latin_id.append(rule->GetLatinName());
        }
      }

      // If the ID has a language tag, copy it.
      {
        const std::string& id = (*it)->GetId();
        std::string::size_type pos = id.rfind("--");
        if (pos != std::string::npos) {
          human_id.append(id, pos, id.size() - pos);
        }
      }

      rule_index_->insert(std::make_pair(human_id, *it));

      // Add the Latin script ID, if a Latin script name could be found for
      // every part of the ID.
      if (std::count(human_id.begin(), human_id.end(), '/') ==
          std::count(latin_id.begin(), latin_id.end(), '/')) {
        rule_index_->insert(std::make_pair(latin_id, *it));
      }
    }

  callback:
    loaded_(success, region_code_, rule_count);
    delete this;
  }

  const std::string region_code_;
  const PreloadSupplier::Callback& loaded_;
  std::set<std::string>* const pending_;
  IndexMap* const rule_index_;
  std::vector<const Rule*>* const rule_storage_;
  const scoped_ptr<const Retriever::Callback> retrieved_;

  DISALLOW_COPY_AND_ASSIGN(Helper);
};

std::string KeyFromRegionCode(const std::string& region_code) {
  AddressData address;
  address.region_code = region_code;
  LookupKey lookup_key;
  lookup_key.FromAddress(address);
  return lookup_key.ToKeyString(0);  // Zero depth = COUNTRY level.
}

}  // namespace

PreloadSupplier::PreloadSupplier(const std::string& validation_data_url,
                                 const Downloader* downloader,
                                 Storage* storage)
    : retriever_(new Retriever(validation_data_url, downloader, storage)),
      pending_(),
      rule_index_(new IndexMap),
      rule_storage_() {}

PreloadSupplier::~PreloadSupplier() {
  for (std::vector<const Rule*>::const_iterator
       it = rule_storage_.begin(); it != rule_storage_.end(); ++it) {
    delete *it;
  }
}

void PreloadSupplier::Supply(const LookupKey& lookup_key,
                             const Supplier::Callback& supplied) {
  Supplier::RuleHierarchy hierarchy;
  bool success = GetRuleHierarchy(lookup_key, &hierarchy);
  supplied(success, lookup_key, hierarchy);
}

const Rule* PreloadSupplier::GetRule(const LookupKey& lookup_key) const {
  assert(IsLoaded(lookup_key.GetRegionCode()));
  Supplier::RuleHierarchy hierarchy;
  if (!GetRuleHierarchy(lookup_key, &hierarchy)) {
    return NULL;
  }
  return hierarchy.rule[lookup_key.GetDepth()];
}

void PreloadSupplier::LoadRules(const std::string& region_code,
                                const Callback& loaded) {
  const std::string& key = KeyFromRegionCode(region_code);

  if (IsLoadedKey(key)) {
    loaded(true, region_code, 0);
    return;
  }

  if (IsPendingKey(key)) {
    return;
  }

  new Helper(
      region_code,
      key,
      loaded,
      *retriever_,
      &pending_,
      rule_index_.get(),
      &rule_storage_);
}

bool PreloadSupplier::IsLoaded(const std::string& region_code) const {
  return IsLoadedKey(KeyFromRegionCode(region_code));
}

bool PreloadSupplier::IsPending(const std::string& region_code) const {
  return IsPendingKey(KeyFromRegionCode(region_code));
}

bool PreloadSupplier::GetRuleHierarchy(const LookupKey& lookup_key,
                                       RuleHierarchy* hierarchy) const {
  assert(hierarchy != NULL);

  if (RegionDataConstants::IsSupported(lookup_key.GetRegionCode())) {
    size_t max_depth = std::min(
        lookup_key.GetDepth(),
        RegionDataConstants::GetMaxLookupKeyDepth(lookup_key.GetRegionCode()));

    for (size_t depth = 0; depth <= max_depth; ++depth) {
      const std::string& key = lookup_key.ToKeyString(depth);
      std::map<std::string, const Rule*>::const_iterator it =
          rule_index_->find(key);
      if (it == rule_index_->end()) {
        return depth > 0;  // No data on COUNTRY level is failure.
      }
      hierarchy->rule[depth] = it->second;
    }
  }

  return true;
}

bool PreloadSupplier::IsLoadedKey(const std::string& key) const {
  return rule_index_->find(key) != rule_index_->end();
}

bool PreloadSupplier::IsPendingKey(const std::string& key) const {
  return pending_.find(key) != pending_.end();
}

}  // namespace addressinput
}  // namespace i18n
