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
// A fake storage object to use in tests. Stores data in memory instead of
// writing it to disk. All operations are synchronous.

#ifndef I18N_ADDRESSINPUT_FAKE_STORAGE_H_
#define I18N_ADDRESSINPUT_FAKE_STORAGE_H_

#include <libaddressinput/storage.h>
#include <libaddressinput/util/basictypes.h>

#include <map>
#include <string>

namespace i18n {
namespace addressinput {

// Stores data in memory. Sample usage:
//    class MyClass {
//     public:
//      MyClass() : storage_(),
//                  data_ready_(BuildCallback(this, &MyClass::OnDataReady)) {}
//
//      ~MyClass() {}
//
//      void Write() {
//        storage_.Put("key", "value");
//      }
//
//      void Read() {
//        storage_.Get("key", *data_ready_);
//      }
//
//     private:
//      void OnDataReady(bool success,
//                       const std::string& key,
//                       std::string* data) {
//        ...
//        delete data;
//      }
//
//      FakeStorage storage_;
//      const scoped_ptr<const Storage::Callback> data_ready_;
//
//      DISALLOW_COPY_AND_ASSIGN(MyClass);
//    };
class FakeStorage : public Storage {
 public:
  FakeStorage();
  virtual ~FakeStorage();

  // Storage implementation.
  virtual void Put(const std::string& key, std::string* data);
  virtual void Get(const std::string& key, const Callback& data_ready) const;

 private:
  std::map<std::string, std::string*> data_;
  DISALLOW_COPY_AND_ASSIGN(FakeStorage);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_FAKE_STORAGE_H_
