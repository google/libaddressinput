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

#include <cassert>
#include <optional>
#include <string>
#include <utility>

namespace i18n {
namespace addressinput {

FakeStorage::FakeStorage() = default;

FakeStorage::~FakeStorage() = default;

void FakeStorage::Put(const std::string& key, std::string data) {
  auto result = data_.emplace(key, data);
  if (!result.second) {
    // Replace data in existing entry for this key.
    result.first->second = std::move(data);
  }
}

void FakeStorage::Get(const std::string& key,
                      const Callback& data_ready) const {
  auto data_it = data_.find(key);
  bool success = data_it != data_.end();
  data_ready(success, key,
             success ? std::make_optional<std::string>(data_it->second)
                     : std::nullopt);
}

}  // namespace addressinput
}  // namespace i18n
