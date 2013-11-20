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
// An object to store a pointer to a method in an object with the following
// signature:
//
//    void Observer::ObserveEvent(bool success,
//                                const Key& key,
//                                const Data& data);

#ifndef I18N_ADDRESSINPUT_CALLBACK_H_
#define I18N_ADDRESSINPUT_CALLBACK_H_

#include <cassert>
#include <cstddef>

namespace i18n {
namespace addressinput {

// Stores a pointer to a method in an object. Sample usage:
//    class MyClass {
//     public:
//      void GetDataAsynchronously() {
//        Callback<MyClass, MyKeyType, MyDataType> callback(
//            this, &MyClass::MyCallback);
//        bool success = ...
//        MyKeyType key = ...
//        MyDataType data = ...
//        callback(success, key, data);
//      }
//
//      void MyCallback(bool success,
//                      const MyKeyType& key,
//                      const MyDataType& data) {
//        ...
//      }
//    };
template <typename Observer, typename Key, typename Data>
class Callback {
 public:
  typedef void (Observer::*ObserveEvent)(bool, const Key&, const Data&);

  Callback(Observer* observer, ObserveEvent observe_event)
      : observer_(observer),
        observe_event_(observe_event) {
    assert(observer_ != NULL);
    assert(observe_event_ != NULL);
  }

  ~Callback() {}

  void operator()(bool success, const Key& key, const Data& data) const {
    (observer_->*observe_event_)(success, key, data);
  }

 private:
  Observer* observer_;
  ObserveEvent observe_event_;
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_CALLBACK_H_
