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

#include "fake_downloader.h"

#include <cassert>
#include <fstream>
#include <map>
#include <string>
#include <utility>

#include "lookup_key_util.h"

namespace i18n {
namespace addressinput {

// static
const char FakeDownloader::kFakeDataUrl[] = "test:///";

namespace {

// The name of the test data file.
const char kDataFileName[] = TEST_DATA_DIR "/countryinfo.txt";

// The number of characters in the fake data URL prefix.
const size_t kFakeDataUrlLength = sizeof FakeDownloader::kFakeDataUrl - 1;

const LookupKeyUtil& GetLookupKeyUtil() {
  static const LookupKeyUtil kLookupKeyUtil(FakeDownloader::kFakeDataUrl);
  return kLookupKeyUtil;
}

std::map<std::string, std::string> InitData() {
  std::map<std::string, std::string> data;
  std::ifstream file(kDataFileName);
  assert(file.is_open());

  std::string line;
  while (file.good()) {
    std::getline(file, line);
    std::string::size_type divider = line.find('=');
    if (divider != std::string::npos) {
      data.insert(std::make_pair(
          GetLookupKeyUtil().GetUrlForKey(line.substr(0, divider)),
          line.substr(divider + 1)));
    }
  }
  file.close();
  return data;
}

const std::map<std::string, std::string>& GetData() {
  static const std::map<std::string, std::string> kData(InitData());
  return kData;
}

}  // namespace

FakeDownloader::FakeDownloader() {}

FakeDownloader::~FakeDownloader() {}

void FakeDownloader::Download(const std::string& url,
                              const Callback& downloaded) const {
  std::map<std::string, std::string>::const_iterator data_it =
      GetData().find(url);
  bool success = data_it != GetData().end();
  std::string data = success ? data_it->second : std::string();
  if (!success && GetLookupKeyUtil().IsValidationDataUrl(url)) {
    // URLs that start with "https://i18napis.appspot.com/ssl-address/" prefix,
    // but do not have associated data will always return "{}" with status code
    // 200. FakeDownloader imitates this behavior for URLs that start with
    // "test:///" prefix.
    success = true;
    data = "{}";
  }
  downloaded(success, url, data);
}

}  // namespace addressinput
}  // namespace i18n
