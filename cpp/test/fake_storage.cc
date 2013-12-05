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

#include "fake_storage.h"

#include <map>
#include <string>

namespace i18n {
namespace addressinput {

FakeStorage::FakeStorage() {}

FakeStorage::~FakeStorage() {}

void FakeStorage::Put(const std::string& key, const std::string& data) {
  data_[key] = data;
}

void FakeStorage::Get(const std::string& key,
                      const Callback& data_ready) const {
  std::map<std::string, std::string>::const_iterator data_it = data_.find(key);
  bool success = data_it != data_.end();
  std::string data = success ? data_it->second : std::string();
  data_ready(success, key, data);
}

}  // namespace addressinput
}  // namespace i18n
