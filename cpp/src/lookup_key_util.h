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
//
// Functions for working with lookup keys. The lookup keys are strings that
// identify serialized validation rules.

#ifndef I18N_ADDRESSINPUT_LOOKUP_KEY_UTIL_H_
#define I18N_ADDRESSINPUT_LOOKUP_KEY_UTIL_H_

#include <string>

namespace i18n {
namespace addressinput {

// Utility functions for lookup keys. Sample usage:
//    LookupKeyUtil lookup_keys("https://i18napis.appspot.com/ssl-address/");
//    Download(lookup_keys.GetUrlForKey("data/US"));
class LookupKeyUtil {
 public:
  // Builds a lookup key utility for the |validation_data_url| parameter. The
  // parameter must end with a '/'.
  explicit LookupKeyUtil(const std::string& validation_data_url);
  ~LookupKeyUtil();

  // Returns the URL where the |key| can be retrieved. For example, returns
  // "https://i18napis.appspot.com/ssl-address/data/US" for input "data/US".
  // Assumes that the input string is a valid URL segment.
  std::string GetUrlForKey(const std::string& key) const;

  // Returns the key for the |url|. For example, returns "data/US" for
  // "https://i18napis.appspot.com/ssl-address/data/US". If the |url| does not
  // start with |validation_data_url| that was passed to the constructor, then
  // returns an empty string. (This can happen if the user of the library
  // returns a bad URL in their Downloader implementation.)
  std::string GetKeyForUrl(const std::string& url) const;

  // Returns true if the |url| starts with |validation_data_url| that was passed
  // to the constructor.
  bool IsValidationDataUrl(const std::string& url) const;

 private:
  const std::string validation_data_url_;
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_LOOKUP_KEY_UTIL_H_
