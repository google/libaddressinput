// Copyright (C) 2013 Google Inc.
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

#ifndef I18N_ADDRESSINPUT_ADDRESS_UI_H_
#define I18N_ADDRESSINPUT_ADDRESS_UI_H_

#include <string>
#include <vector>

namespace i18n {
namespace addressinput {

class Localization;
struct AddressUiComponent;

// Returns the list of supported CLDR region codes.
const std::vector<std::string>& GetRegionCodes();

// Returns the UI components for the CLDR |region_code|. Uses the strings from
// |localization|. Returns an empty vector on error.
std::vector<AddressUiComponent> BuildComponents(
    const std::string& region_code,
    const Localization& localization);

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_ADDRESS_UI_H_
