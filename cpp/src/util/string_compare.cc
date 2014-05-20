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

#include "re2ptr.h"  // Must be the first #include statement!

#include "string_compare.h"

#include <libaddressinput/util/basictypes.h>

#include <string>

namespace i18n {
namespace addressinput {

class StringCompare::Impl {
 public:
  Impl() {
    options_.set_literal(true);
    options_.set_case_sensitive(false);
  }

  ~Impl() {}

  bool NaturalEquals(const std::string& a, const std::string& b) const {
    RE2 matcher(b, options_);
    return RE2::FullMatch(a, matcher);
  }

 private:
  RE2::Options options_;

  DISALLOW_COPY_AND_ASSIGN(Impl);
};

StringCompare::StringCompare() : impl_(new Impl) {}

StringCompare::~StringCompare() {}

bool StringCompare::NaturalEquals(const std::string& a,
                                  const std::string& b) const {
  return impl_->NaturalEquals(a, b);
}

}  // namespace addressinput
}  // namespace i18n
