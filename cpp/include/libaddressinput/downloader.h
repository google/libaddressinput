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
// The interface to be implemented by the user of the library to enable
// downloading validation rules from a server.

#ifndef I18N_ADDRESSINPUT_DOWNLOADER_H_
#define I18N_ADDRESSINPUT_DOWNLOADER_H_

#include <libaddressinput/callback.h>

#include <string>

namespace i18n {
namespace addressinput {

// Downloads validation rules from the server. Sample usage:
//    class MyDownloader : public Downloader {
//     public:
//      virtual void Download(const std::string& url,
//                            const Callback& downloaded) const {
//        bool success = ...
//        std::string data = ...
//        downloaded(success, url, data);
//      }
//    };
class Downloader {
 public:
  typedef i18n::addressinput::Callback<std::string, std::string> Callback;

  virtual ~Downloader() {}

  // Downloads |url| and invokes the |downloaded| callback.
  virtual void Download(const std::string& url,
                        const Callback& downloaded) const = 0;
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_DOWNLOADER_H_
