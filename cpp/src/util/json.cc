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

#include "json.h"

#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <cassert>
#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/reader.h>

namespace i18n {
namespace addressinput {

using rapidjson::Document;
using rapidjson::kParseValidateEncodingFlag;
using rapidjson::Value;

class Json::JsonImpl {
 public:
  explicit JsonImpl(const std::string& json)
      : document_(new Document),
        value_(document_.get()),
        dictionaries_(),
        keys_(),
        valid_(false) {
    document_->Parse<kParseValidateEncodingFlag>(json.c_str());
    valid_ = !document_->HasParseError() && document_->IsObject();
    if (valid_) {
      BuildKeyList();
    }
  }

  ~JsonImpl() {
    for (std::map<std::string, const Json*>::const_iterator
         it = dictionaries_.begin();
         it != dictionaries_.end();
         ++it) {
      delete it->second;
    }
  }

  bool valid() const { return valid_; }

  const std::vector<std::string>& GetKeys() const { return keys_; }

  bool GetStringValueForKey(const std::string& key, std::string* value) const {
    assert(value != NULL);

    Value::ConstMemberIterator member = value_->FindMember(key.c_str());
    if (member == NULL || !member->value.IsString()) {
      return false;
    }

    value->assign(member->value.GetString(),
                  member->value.GetStringLength());
    return true;
  }

  bool GetDictionaryValueForKey(const std::string& key, const Json** value) {
    assert(value != NULL);

    std::map<std::string, const Json*>::const_iterator dict_it =
        dictionaries_.find(key);
    if (dict_it != dictionaries_.end()) {
      *value = dict_it->second;
      return true;
    }

    Value::ConstMemberIterator member = value_->FindMember(key.c_str());
    if (member == NULL || !member->value.IsObject()) {
      return false;
    }

    std::pair<std::map<std::string, const Json*>::iterator, bool> result =
        dictionaries_.insert(
            std::make_pair(key, new Json(new JsonImpl(&member->value))));
    assert(result.second);
    *value = result.first->second;
    return true;
  }

 private:
  // Does not take ownership of |value|.
  explicit JsonImpl(const Value* value)
      : document_(),
        value_(value),
        dictionaries_(),
        keys_(),
        valid_(true) {
    assert(value_ != NULL);
    assert(value_->IsObject());
    BuildKeyList();
  }

  void BuildKeyList() {
    assert(keys_.empty());
    for (Value::ConstMemberIterator member = value_->MemberBegin();
         member != value_->MemberEnd(); ++member) {
      keys_.push_back(member->name.GetString());
    }
  }

  // An owned JSON document. Can be NULL if the JSON document is not owned.
  const scoped_ptr<Document> document_;

  // A JSON document that is not owned. Cannot be NULL. Can point to document_.
  const Value* const value_;

  // Owned JSON objects.
  std::map<std::string, const Json*> dictionaries_;

  // The list of keys with values in the JSON object.
  std::vector<std::string> keys_;

  // True if the JSON object was parsed successfully.
  bool valid_;

  DISALLOW_COPY_AND_ASSIGN(JsonImpl);
};

Json::Json() : impl_() {}

Json::~Json() {}

bool Json::ParseObject(const std::string& json) {
  assert(impl_ == NULL);
  impl_.reset(new JsonImpl(json));
  if (!impl_->valid()) {
    impl_.reset();
  }
  return impl_ != NULL;
}

const std::vector<std::string>& Json::GetKeys() const {
  assert(impl_ != NULL);
  return impl_->GetKeys();
}

bool Json::GetStringValueForKey(const std::string& key,
                                std::string* value) const {
  assert(impl_ != NULL);
  return impl_->GetStringValueForKey(key, value);
}

bool Json::GetDictionaryValueForKey(const std::string& key,
                                    const Json** value) const {
  assert(impl_ != NULL);
  return impl_->GetDictionaryValueForKey(key, value);
}

Json::Json(JsonImpl* impl) : impl_(impl) {}

}  // namespace addressinput
}  // namespace i18n
