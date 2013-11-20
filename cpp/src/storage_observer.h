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
// The base class for observers of a Storage object.

#ifndef I18N_ADDRESSINPUT_STORAGE_OBSERVER_H_
#define I18N_ADDRESSINPUT_STORAGE_OBSERVER_H_

#include <libaddressinput/storage.h>

#include <string>

namespace i18n {
namespace addressinput {

// Observes storage events. Sample usage:
//    class MyClass : public StorageObserver {
//     public:
//      void Read() {
//        storage_->Get("key", BuildDataReadyCallback());
//      }
//
//      virtual void OnDataReady(bool success,
//                               const std::string& key,
//                               const std::string& data) {
//        ...
//      }
//
//     private:
//      scoped_ptr<Storage> storage_;
//    };
class StorageObserver {
 public:
  virtual ~StorageObserver() {}

  virtual void OnDataReady(bool success,
                           const std::string& key,
                           const std::string& data) = 0;

 protected:
  Storage::DataReadyCallback BuildDataReadyCallback() {
    return Storage::DataReadyCallback(this, &StorageObserver::OnDataReady);
  }
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_STORAGE_OBSERVER_H_
