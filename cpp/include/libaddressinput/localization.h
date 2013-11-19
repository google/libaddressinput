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

#ifndef I18N_ADDRESSINPUT_LOCALIZATION_H_
#define I18N_ADDRESSINPUT_LOCALIZATION_H_

#include <string>

namespace i18n {
namespace addressinput {

// The object to retrieve localized strings based on message IDs. Sample usage:
//    Localization localization;
//    localization.SetLanguage("en");
//    Process(BuildComponents("CA", localization));
//
// Alternative usage:
//    Localization localization;
//    localization.SetGetter(&MyStringGetter);
//    Process(BuildComponents("CA", localization));
class Localization {
 public:
  // Initializes with English messages by default.
  Localization();
  ~Localization();

  // Returns the localized string for |message_id|. Returns an empty string if
  // there's no message with this identifier.
  std::string GetString(int message_id) const;

  // Sets the language for the strings. The only supported language is "en"
  // until we have translations.
  void SetLanguage(const std::string& language_code);

  // Sets the string getter that takes a message identifier and returns the
  // corresponding localized string.
  void SetGetter(std::string (*getter)(int));

 private:
  // The string getter.
  std::string (*get_string_)(int);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_LOCALIZATION_H_
