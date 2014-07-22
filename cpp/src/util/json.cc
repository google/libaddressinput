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
  // Takes ownership of |document|.
  explicit JsonImpl(const Document* document)
      : document_(document), value_(document), dictionaries_() {
    assert(value_ != NULL);
    assert(value_->IsObject());
    BuildKeyList();
  }

  // Does not take ownership of |value|.
  explicit JsonImpl(const Value* value)
      : document_(), value_(value), dictionaries_() {
    assert(value_ != NULL);
    assert(value_->IsObject());
    BuildKeyList();
  }

  ~JsonImpl() {
    for (std::map<std::string, const Json*>::const_iterator
         it = dictionaries_.begin();
         it != dictionaries_.end(); ++it) {
      delete it->second;
    }
  }

  // The caller does not own the result.
  const Value::Member* FindMember(const std::string& key) {
    return value_->FindMember(key.c_str());
  }

  // The caller does not own the result. The result can be NULL if there's no
  // dictionary for |key|.
  const Json* FindDictionary(const std::string& key) const {
    std::map<std::string, const Json*>::const_iterator it =
        dictionaries_.find(key);
    return it != dictionaries_.end() ? it->second : NULL;
  }

  // Takes ownership of |dictionary|. Should be called only once per |key| and
  // per |dictionary|.
  void AddDictionary(const std::string& key, const Json* dictionary) {
    bool inserted =
        dictionaries_.insert(std::make_pair(key, dictionary)).second;
    // Cannot do work inside of assert(), because the compiler can optimize it
    // away.
    assert(inserted);
    // Avoid unused variable warning when assert() is optimized away.
    (void)inserted;
  }

  const std::vector<std::string>& GetKeys() const { return keys_; }

 private:
  void BuildKeyList() {
    assert(keys_.empty());
    for (Value::ConstMemberIterator it = value_->MemberBegin();
         it != value_->MemberEnd(); ++it) {
      keys_.push_back(it->name.GetString());
    }
  }

  // An owned JSON document. Can be NULL if the JSON document is not owned.
  //
  // When a JsonImpl object is constructed using a Document object, then
  // JsonImpl is supposed to take ownership of that object, making sure to
  // delete it in its own destructor. But when a JsonImpl object is constructed
  // using a Value object, then that object is owned by a Member object which is
  // owned by a Document object, and should therefore not be deleted by
  // JsonImpl.
  const scoped_ptr<const Document> document_;

  // A JSON document that is not owned. Cannot be NULL. Can point to document_.
  const Value* const value_;

  // Owned JSON objects.
  std::map<std::string, const Json*> dictionaries_;

  std::vector<std::string> keys_;

  DISALLOW_COPY_AND_ASSIGN(JsonImpl);
};

Json::Json() {}

Json::~Json() {}

bool Json::ParseObject(const std::string& json) {
  assert(impl_ == NULL);
  scoped_ptr<Document> document(new Document);
  document->Parse<kParseValidateEncodingFlag>(json.c_str());
  bool valid = !document->HasParseError() && document->IsObject();
  if (valid) {
    impl_.reset(new JsonImpl(document.release()));
  }
  return valid;
}

const std::vector<std::string>& Json::GetKeys() const {
  assert(impl_ != NULL);
  return impl_->GetKeys();
}

bool Json::GetStringValueForKey(const std::string& key,
                                std::string* value) const {
  assert(impl_ != NULL);
  assert(value != NULL);

  // Member is owned by impl_.
  const Value::Member* member = impl_->FindMember(key.c_str());
  if (member == NULL || !member->value.IsString()) {
    return false;
  }

  value->assign(member->value.GetString(), member->value.GetStringLength());
  return true;
}

bool Json::HasDictionaryValueForKey(const std::string& key) const {
  assert(impl_ != NULL);

  // The value returned by FindDictionary() is owned by impl_.
  if (impl_->FindDictionary(key) != NULL) {
    return true;
  }

  // Member is owned by impl_.
  const Value::Member* member = impl_->FindMember(key);
  return member != NULL && member->value.IsObject();
}

const Json& Json::GetDictionaryValueForKey(const std::string& key) const {
  assert(impl_ != NULL);

  // Existing_dictionary is owned by impl_.
  const Json* existing_dictionary = impl_->FindDictionary(key);
  if (existing_dictionary != NULL) {
    return *existing_dictionary;
  }

  // Member is owned by impl_.
  const Value::Member* member = impl_->FindMember(key);
  assert(member != NULL);
  assert(member->value.IsObject());

  // Dictionary is owned by impl_.
  Json* dictionary = new Json;
  dictionary->impl_.reset(new JsonImpl(&member->value));
  impl_->AddDictionary(key, dictionary);
  return *dictionary;
}

}  // namespace addressinput
}  // namespace i18n
