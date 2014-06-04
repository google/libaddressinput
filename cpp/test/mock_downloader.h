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
// A mock downloader object to use in tests.

#ifndef I18N_ADDRESSINPUT_TEST_MOCK_DOWNLOADER_H_
#define I18N_ADDRESSINPUT_TEST_MOCK_DOWNLOADER_H_

#include <libaddressinput/downloader.h>

#include <map>
#include <string>

#include <libaddressinput/util/basictypes.h>

namespace i18n {
namespace addressinput {

// "Downloads" serialized validation rules from a key-value map. Sample usage:
//    class MyClass {
//     public:
//      MyClass() : downloader_(),
//                  callback_(BuildCallback(this, &MyClass::OnDownloaded)) {
//        downloader_.data_.insert(
//            std::make_pair("data/XA", "{\"id\":\"data/XA\"}"));
//      }
//
//      ~MyClass() {}
//
//      void GetData(const std::string& key) {
//        downloader_.Download(std::string(MockDownloader::kMockDataUrl) + key,
//                             *callback_);
//      }
//
//     private:
//      void OnDownloaded(bool success,
//                        const std::string& url,
//                        const std::string& data) {
//        ...
//      }
//
//      MockDownloader downloader_;
//      const scoped_ptr<const Downloader::Callback> callback_;
//
//      DISALLOW_COPY_AND_ASSIGN(MyClass);
//    };
class MockDownloader : public Downloader {
 public:
  // The mock data URL to be used in tests.
  static const char kMockDataUrl[];

  MockDownloader();
  virtual ~MockDownloader();

  // Downloader implementation.
  virtual void Download(const std::string& url,
                        const Callback& downloaded) const;

  std::map<std::string, std::string> data_;

 private:
  DISALLOW_COPY_AND_ASSIGN(MockDownloader);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_TEST_MOCK_DOWNLOADER_H_
