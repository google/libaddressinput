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
//
// It is not always desirable to cache libaddressinput data. Sometimes it might
// give better performance characteristics to not cache. This implementation of
// the Storage interface therefore doesn't actually store anything.

#ifndef I18N_ADDRESSINPUT_NULL_STORAGE_H_
#define I18N_ADDRESSINPUT_NULL_STORAGE_H_

#include <libaddressinput/storage.h>
#include <libaddressinput/util/basictypes.h>

#include <string>

namespace i18n {
namespace addressinput {

class NullStorage : public Storage {
 public:
  NullStorage();
  virtual ~NullStorage();

  // No-op.
  virtual void Put(const std::string& key, std::string* data);

  // Always calls the |data_ready| callback function signalling failure.
  virtual void Get(const std::string& key, const Callback& data_ready) const;

 private:
  DISALLOW_COPY_AND_ASSIGN(NullStorage);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_NULL_STORAGE_H_
