// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// The original source code is from:
// http://src.chromium.org/viewvc/chrome/trunk/src/base/strings/string_util.cc?revision=268754
//
// Modified to contain only the DoReplaceStringPlaceholders() that works with
// std::string. Replaced DCHECK() with assert() and removed offsets.

#include "string_util.h"

#include <libaddressinput/util/basictypes.h>

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

namespace {

// Used by ReplaceStringPlaceholders to track the position in the string of
// replaced parameters.
struct ReplacementOffset {
  ReplacementOffset(uintptr_t parameter, size_t offset)
      : parameter(parameter),
        offset(offset) {}

  // Index of the parameter.
  uintptr_t parameter;

  // Starting position in the string.
  size_t offset;
};

static bool CompareParameter(const ReplacementOffset& elem1,
                             const ReplacementOffset& elem2) {
  return elem1.parameter < elem2.parameter;
}

}  // namespace

namespace i18n {
namespace addressinput {

std::string DoReplaceStringPlaceholders(const std::string& format_string,
                                        const std::vector<std::string>& subst) {
  size_t substitutions = subst.size();

  size_t sub_length = 0;
  for (typename std::vector<std::string>::const_iterator iter = subst.begin();
       iter != subst.end(); ++iter) {
    sub_length += iter->length();
  }

  std::string formatted;
  formatted.reserve(format_string.length() + sub_length);

  std::vector<ReplacementOffset> r_offsets;
  for (typename std::string::const_iterator i = format_string.begin();
       i != format_string.end(); ++i) {
    if ('$' == *i) {
      if (i + 1 != format_string.end()) {
        ++i;
        assert('$' == *i || '1' <= *i);
        if ('$' == *i) {
          while (i != format_string.end() && '$' == *i) {
            formatted.push_back('$');
            ++i;
          }
          --i;
        } else {
          uintptr_t index = 0;
          while (i != format_string.end() && '0' <= *i && *i <= '9') {
            index *= 10;
            index += *i - '0';
            ++i;
          }
          --i;
          index -= 1;
          if (index < substitutions)
            formatted.append(subst.at(index));
        }
      }
    } else {
      formatted.push_back(*i);
    }
  }
  return formatted;
}

}  // addressinput
}  // i18n
