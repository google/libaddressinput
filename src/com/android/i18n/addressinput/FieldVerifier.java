/*
 * Copyright (C) 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.i18n.addressinput;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.regex.Pattern;

/**
 * API to access address verification data used to verify components of an
 * address. Each API implements a different form of verification.
 * <p>
 * Not all fields require all types of validation, although the APIs are
 * designed so that this could be done. In particular, the current
 * implementation only provides known value verification for the hierarchical
 * fields, and only provides format and match verification for the postal code
 * field.
 */
public class FieldVerifier {
  // TODO: remove initialisers. Here to silence compile errors.
  private final Set<AddressField> used = new HashSet<AddressField>();
  private final Set<AddressField> required = new HashSet<AddressField>();
  // Known values. Can be either a key, a name in Latin, or a name in native script.
  private final Map<String, String> known = new HashMap<String, String>();
  private final String[] keys = {};
  // Names in Latin.
  private final String[] lnames = {};
  // Names in native script.
  private final String[] names = {};
  private final Pattern format = Pattern.compile("");
  private final Pattern match = Pattern.compile("");
  // TODO: Partial port only. This is only added so code compiles. The check() function below should
  // work.

  FieldVerifier refineVerifier(String sublevel) {
    // TODO: Replace with real implemenation.
    return new FieldVerifier();
  }

  public void report(AddressProblemType problem, AddressField field, String value,
                     AddressProblems problems) {
    problems.add(field, problem);
  }

  public boolean check(LookupKey.ScriptType script, AddressProblemType problem, AddressField field,
                       String value, AddressProblems problems) {
    // Assume success.
    boolean result = true;

    String trimmedValue = Util.trimToNull(value);
    switch (problem) {
      case UNUSED_FIELD:
        result = (trimmedValue == null) || used.contains(field);
        break;
      case MISSING_REQUIRED_FIELD:
        result = !((trimmedValue == null) && required.contains(field));
        break;
      case UNKNOWN_VALUE:
        // An empty string will never be an UNKNOWN_VALUE. It is invalid
        // only when it appears in a required field (In that case it will
        // be reported as MISSING_REQUIRED_FIELD).
        if (trimmedValue == null) {
          break;
        }
        result = isKnownInScript(script, value);
        break;
      case UNRECOGNIZED_FORMAT:
        result = (trimmedValue == null) || (format == null)
            || format.matcher(value == null ? "" : value).matches();
        break;
      case MISMATCHING_VALUE:
        result = (trimmedValue == null) || (match == null)
            || match.matcher(value == null ? "" : value).lookingAt();
        break;
      default:
        throw new RuntimeException("unknown problem: " + problem);
    }
    if (!result) {
      report(problem, field, value, problems);
    }
    return result;
  }

  private boolean isKnownInScript(LookupKey.ScriptType script, String value) {
    String trimmedValue = Util.trimToNull(value);
    Util.checkNotNull(trimmedValue);
    // If script is null, checks against all known values.
    if (script == null) {
      return known == null || known.containsKey(trimmedValue.toLowerCase());
    }
    String[] currNames =
         script == LookupKey.ScriptType.LATIN ? lnames : names;
    Set<String> candidates = new HashSet<String>();
    if (currNames != null) {
      for (String name : currNames) {
        candidates.add(name.toLowerCase());
      }
    }
    if (keys != null) {
      for (String name : keys) {
        candidates.add(name.toLowerCase());
      }
    }

    if (candidates.size() == 0 || trimmedValue == null) {
      return true;
    }

    return candidates.contains(value.toLowerCase());
  }

  public String toString() {
    // TODO: Replace with real implementation
    return "";
  }
}
