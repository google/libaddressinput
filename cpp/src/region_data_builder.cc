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

#include <libaddressinput/region_data_builder.h>

#include <libaddressinput/address_data.h>
#include <libaddressinput/preload_supplier.h>
#include <libaddressinput/region_data.h>

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "language.h"
#include "lookup_key.h"
#include "region_data_constants.h"
#include "rule.h"

namespace i18n {
namespace addressinput {

namespace {

// Does not take ownership of |supplier| or |parent_region|, neither of which is
// allowed to be NULL.
void BuildRegionTreeRecursively(PreloadSupplier* supplier,
                                const LookupKey& parent_key,
                                RegionData* parent_region,
                                const std::vector<std::string>& keys,
                                bool prefer_latin_name) {
  assert(supplier != NULL);
  assert(parent_region != NULL);

  LookupKey lookup_key;
  for (std::vector<std::string>::const_iterator key_it = keys.begin();
       key_it != keys.end(); ++key_it) {
    lookup_key.FromLookupKey(parent_key, *key_it);
    const Rule* rule = supplier->GetRule(lookup_key);
    if (rule == NULL) {
      return;
    }
    const std::string& local_name = rule->GetName().empty()
        ? *key_it : rule->GetName();
    const std::string& name =
        prefer_latin_name && !rule->GetLatinName().empty()
            ? rule->GetLatinName() : local_name;
    RegionData* region = parent_region->AddSubRegion(*key_it, name);
    if (!rule->GetSubKeys().empty()) {
      BuildRegionTreeRecursively(
          supplier, lookup_key, region, rule->GetSubKeys(), prefer_latin_name);
    }
  }
}

// Does not take ownership of |supplier|, which cannot be NULL. The caller owns
// the result.
RegionData* BuildRegion(PreloadSupplier* supplier,
                        const std::string& region_code,
                        const Language& language) {
  assert(supplier != NULL);

  AddressData address;
  address.region_code = region_code;

  LookupKey lookup_key;
  lookup_key.FromAddress(address);

  const Rule* const rule = supplier->GetRule(lookup_key);
  assert(rule != NULL);

  RegionData* region = new RegionData(region_code);
  BuildRegionTreeRecursively(supplier,
                             lookup_key,
                             region,
                             rule->GetSubKeys(),
                             language.has_latin_script);

  return region;
}

}  // namespace

RegionDataBuilder::RegionDataBuilder(PreloadSupplier* supplier)
    : supplier_(supplier),
      cache_() {
  assert(supplier_ != NULL);
}

RegionDataBuilder::~RegionDataBuilder() {
  for (RegionCodeDataMap::const_iterator region_it = cache_.begin();
       region_it != cache_.end(); ++region_it) {
    for (LanguageRegionMap::const_iterator
         language_it = region_it->second->begin();
         language_it != region_it->second->end(); ++language_it) {
      delete language_it->second;
    }
    delete region_it->second;
  }
}

const RegionData& RegionDataBuilder::Build(
    const std::string& region_code,
    const std::string& ui_language_tag,
    std::string* best_region_tree_language_tag) {
  assert(supplier_->IsLoaded(region_code));
  assert(best_region_tree_language_tag != NULL);

  // Look up the region tree in cache first before building it.
  RegionCodeDataMap::const_iterator region_it = cache_.find(region_code);
  if (region_it == cache_.end()) {
    region_it =
        cache_.insert(std::make_pair(region_code, new LanguageRegionMap)).first;
  }

  // No need to copy from default rule first, because only languages and Latin
  // format are going to be used, which do not exist in the default rule.
  Rule rule;
  rule.ParseSerializedRule(RegionDataConstants::GetRegionData(region_code));
  static const Language kUndefinedLanguage("und");
  const Language& best_language =
      rule.GetLanguages().empty()
          ? kUndefinedLanguage
          : ChooseBestAddressLanguage(rule, Language(ui_language_tag));
  *best_region_tree_language_tag = best_language.tag;

  LanguageRegionMap::const_iterator language_it =
      region_it->second->find(best_language.tag);
  if (language_it == region_it->second->end()) {
    language_it =
        region_it->second->insert(std::make_pair(best_language.tag,
                                                 BuildRegion(supplier_,
                                                             region_code,
                                                             best_language)))
            .first;
  }

  return *language_it->second;
}

}  // namespace addressinput
}  // namespace i18n
