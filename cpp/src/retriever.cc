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

#include "retriever.h"

#include <libaddressinput/callback.h>
#include <libaddressinput/downloader.h>
#include <libaddressinput/storage.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <cassert>
#include <cstddef>
#include <string>

#include "lookup_key_util.h"
#include "validating_storage.h"

namespace i18n {
namespace addressinput {

namespace {

class Helper {
 public:
  // Does not take ownership of its parameters.
  Helper(const std::string& key,
         const Retriever::Callback& retrieved,
         const LookupKeyUtil& lookup_key_util,
         const Downloader& downloader,
         ValidatingStorage* storage)
      : retrieved_(retrieved),
        lookup_key_util_(lookup_key_util),
        downloader_(downloader),
        storage_(storage),
        downloaded_(BuildCallback(this, &Helper::OnDownloaded)),
        validated_data_ready_(
            BuildCallback(this, &Helper::OnValidatedDataReady)),
        stale_data_() {
    assert(storage_ != NULL);
    storage_->Get(key, *validated_data_ready_);
  }

 private:
  ~Helper() {}

  void OnValidatedDataReady(bool success,
                            const std::string& key,
                            std::string* data) {
    if (success) {
      assert(data != NULL);
      retrieved_(success, key, *data);
      delete this;
    } else {
      // Validating storage returns (false, key, stale-data) for valid but stale
      // data. If |data| is empty, however, then it's either missing or invalid.
      if (data != NULL && !data->empty()) {
        stale_data_ = *data;
      }
      downloader_.Download(lookup_key_util_.GetUrlForKey(key), *downloaded_);
    }
    delete data;
  }

  void OnDownloaded(bool success, const std::string& url, std::string* data) {
    const std::string& key = lookup_key_util_.GetKeyForUrl(url);
    if (success) {
      assert(data != NULL);
      retrieved_(true, key, *data);
      storage_->Put(key, data);
      data = NULL;  // Deleted by Storage::Put().
    } else if (!stale_data_.empty()) {
      // Reuse the stale data if a download fails. It's better to have slightly
      // outdated validation rules than to suddenly lose validation ability.
      retrieved_(true, key, stale_data_);
    } else {
      retrieved_(false, key, std::string());
    }
    delete data;
    delete this;
  }

  const Retriever::Callback& retrieved_;
  const LookupKeyUtil& lookup_key_util_;
  const Downloader& downloader_;
  ValidatingStorage* storage_;
  const scoped_ptr<const Downloader::Callback> downloaded_;
  const scoped_ptr<const Storage::Callback> validated_data_ready_;
  std::string stale_data_;

  DISALLOW_COPY_AND_ASSIGN(Helper);
};

}  // namespace

Retriever::Retriever(const std::string& validation_data_url,
                     const Downloader* downloader,
                     Storage* storage)
    : lookup_key_util_(validation_data_url),
      downloader_(downloader),
      storage_(new ValidatingStorage(storage)) {
  assert(storage_ != NULL);
  assert(downloader_ != NULL);
}

Retriever::~Retriever() {}

void Retriever::Retrieve(const std::string& key,
                         const Callback& retrieved) const {
  new Helper(key, retrieved, lookup_key_util_, *downloader_, storage_.get());
}

}  // namespace addressinput
}  // namespace i18n
