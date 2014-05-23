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

#ifndef I18N_ADDRESSINPUT_SYNONYMS_H_
#define I18N_ADDRESSINPUT_SYNONYMS_H_

#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

namespace i18n {
namespace addressinput {

class AddressData;
class PreloadSupplier;
class StringCompare;

class Synonyms {
 public:
  // Does not take ownership of |supplier|.
  explicit Synonyms(const PreloadSupplier* supplier);
  ~Synonyms();

  // Converts the names of the administrative subdivisions into canonical names.
  // Should be called only when supplier->IsLoaded() returns true for the region
  // code of the |address|.
  void NormalizeForDisplay(AddressData* address) const;

 private:
  const PreloadSupplier* const supplier_;  // Not owned.
  const scoped_ptr<const StringCompare> compare_;

  DISALLOW_COPY_AND_ASSIGN(Synonyms);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_SYNONYMS_H_
