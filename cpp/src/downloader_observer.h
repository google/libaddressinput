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
// The base class for observers of a Downloader object.

#ifndef I18N_ADDRESSINPUT_DOWNLOADER_OBSERVER_H_
#define I18N_ADDRESSINPUT_DOWNLOADER_OBSERVER_H_

#include <libaddressinput/downloader.h>

#include <string>

namespace i18n {
namespace addressinput {

// Observes download events. Sample usage:
//    class MyClass : public DownloaderObserver {
//     public:
//      void Retrieve() {
//        downloader_->Download(
//            "https://i18napis.appspot.com/ssl-address/data/US",
//            BuildDownloadedCallback());
//      }
//
//      virtual void OnDownloaded(bool success,
//                                const std::string& url,
//                                const std::string& data) {
//        ...
//      }
//
//     private:
//      scoped_ptr<Downloader> downloader_;
//    };
class DownloaderObserver {
 public:
  virtual ~DownloaderObserver() {}

  virtual void OnDownloaded(bool success,
                            const std::string& url,
                            const std::string& data) = 0;

 protected:
  Downloader::DownloadedCallback BuildDownloadedCallback() {
    return Downloader::DownloadedCallback(
        this, &DownloaderObserver::OnDownloaded);
  }
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_DOWNLOADER_OBSERVER_H_
