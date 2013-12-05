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
// A fake downloader object to use in tests. Reads data from a file instead of
// downloading it from a server.

#ifndef I18N_ADDRESSINPUT_TEST_FAKE_DOWNLOADER_H_
#define I18N_ADDRESSINPUT_TEST_FAKE_DOWNLOADER_H_

#include <libaddressinput/downloader.h>

#include <string>

namespace i18n {
namespace addressinput {

// "Downloads" serialized validation rules from a test data file. Sample usage:
//    class MyClass {
//     public:
//      MyClass() : downloader_(),
//                  callback_(BuildCallback(this, &MyClass::OnDownloaded)) {}
//
//      ~MyClass() {}
//
//      void GetData(const std::string& key) {
//        downloader_.Download(std::string(FakeDownloader::kFakeDataUrl) + key,
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
//      FakeDownloader downloader_;
//      scoped_ptr<Downloader::Callback> callback_;
//
//      DISALLOW_COPY_AND_ASSIGN(MyClass);
//    };
class FakeDownloader : public Downloader {
 public:
  // The fake data URL to be used in tests.
  static const char kFakeDataUrl[];

  FakeDownloader();
  virtual ~FakeDownloader();

  // Downloader implementation.
  virtual void Download(const std::string& url,
                        const Callback& downloaded) const;
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_TEST_FAKE_DOWNLOADER_H_
