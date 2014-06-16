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

#include "mock_downloader.h"

#include <cassert>
#include <cstddef>
#include <map>
#include <string>

namespace i18n {
namespace addressinput {

// static
const char MockDownloader::kMockDataUrl[] = "mock:///";

namespace {

// The number of characters in the mock data URL prefix.
const size_t kMockDataUrlLength = sizeof MockDownloader::kMockDataUrl - 1;

}  // namespace

MockDownloader::MockDownloader() {}

MockDownloader::~MockDownloader() {}

void MockDownloader::Download(const std::string& url,
                              const Callback& downloaded) const {
  assert(url.compare(0, kMockDataUrlLength, kMockDataUrl) == 0);
  std::string key(url, kMockDataUrlLength);
  std::map<std::string, std::string>::const_iterator it = data_.find(key);
  bool success = it != data_.end();
  downloaded(success, url, success ? new std::string(it->second) : NULL);
}

}  // namespace addressinput
}  // namespace i18n
