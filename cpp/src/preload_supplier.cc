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

#include <cassert>
#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "language.h"
#include "lookup_key.h"
#include "region_data_constants.h"
#include "retriever.h"
#include "rule.h"
#include "util/json.h"

namespace i18n {
namespace addressinput {

namespace {

class Helper {
 public:
  // Does not take ownership of its parameters.
  Helper(const std::string& region_code,
         const std::string& key,
         const PreloadSupplier::Callback& loaded,
         const Retriever& retriever,
         std::set<std::string>* pending,
         std::map<std::string, const Rule*>* rule_cache)
      : region_code_(region_code),
        loaded_(loaded),
        pending_(pending),
        rule_cache_(rule_cache),
        retrieved_(BuildCallback(this, &Helper::OnRetrieved)) {
    assert(pending_ != NULL);
    assert(rule_cache_ != NULL);
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

      std::pair<std::map<std::string, const Rule*>::iterator, bool> result =
          rule_cache_->insert(std::make_pair(rule->GetId(), rule));
      assert(result.second);
      (void)result;  // Prevent unused variable if assert() is optimized away.
      ++rule_count;
    }

  callback:
    loaded_(success, region_code_, rule_count);
    delete this;
  }

  const std::string region_code_;
  const PreloadSupplier::Callback& loaded_;
  std::set<std::string>* const pending_;
  std::map<std::string, const Rule*>* const rule_cache_;
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
      rule_cache_() {}

PreloadSupplier::~PreloadSupplier() {
  for (std::map<std::string, const Rule*>::const_iterator
       it = rule_cache_.begin(); it != rule_cache_.end(); ++it) {
    delete it->second;
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
  return hierarchy.rule_[lookup_key.GetDepth()];
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
      &rule_cache_);
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
          rule_cache_.find(key);
      if (it == rule_cache_.end()) {
        return depth > 0;  // No data on COUNTRY level is failure.
      }
      hierarchy->rule_[depth] = it->second;
    }
  }

  return true;
}

bool PreloadSupplier::IsLoadedKey(const std::string& key) const {
  return rule_cache_.find(key) != rule_cache_.end();
}

bool PreloadSupplier::IsPendingKey(const std::string& key) const {
  return pending_.find(key) != pending_.end();
}

}  // namespace addressinput
}  // namespace i18n
