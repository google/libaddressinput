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

#include "mock_source.h"

#include <cstddef>
#include <optional>
#include <string>

namespace i18n {
namespace addressinput {

MockSource::MockSource() = default;
MockSource::~MockSource() = default;

void MockSource::Get(const std::string& key, const Callback& data_ready) const {
  auto it = data_.find(key);
  bool success = it != data_.end();
  data_ready(success, key, success ? it->second : std::optional<std::string>());
}

}  // namespace addressinput
}  // namespace i18n
