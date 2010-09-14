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
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Utility functions used by the address widget.
 */
public class Util {
  // In upper-case, since we convert the language code to upper case before doing string comparison.
  private static final String LATIN_SCRIPT = "LATN";

  // Cannot instantiate this class - private constructor.
  private Util() {}

  /**
   * Returns true if the language code is explicitly marked to be in the latin script. For example,
   * "zh-Latn" would return true, but "zh-TW", "en" and "zh" would all return false.
   */
  public static boolean isExplicitLatinScript(String languageCode) {
    // Convert to upper-case for easier comparison.
    languageCode = languageCode.toUpperCase();
    // Check to see if the language code contains a script modifier.
    final Pattern languageCodePattern = Pattern.compile("\\w{2,3}[-_](\\w{4})");
    Matcher m = languageCodePattern.matcher(languageCode);
    if (m.lookingAt()) {
      String script = m.group(1);
      if (script.equals(LATIN_SCRIPT)) {
        return true;
      }
    }
    return false;
  }

  /**
   * Returns the language subtag of a language code. For example, returns "zh" if given "zh-Hans",
   * "zh-CN" or other "zh" variants. If no language subtag can be found or the language tag is
   * malformed, returns "und".
   */
  public static String getLanguageSubtag(String languageCode) {
    final Pattern languageCodePattern = Pattern.compile("(\\w{2,3})(?:[-_]\\w{4})?(?:[-_]\\w{2})?");
    Matcher m = languageCodePattern.matcher(languageCode);
    if (m.matches()) {
      return m.group(1).toLowerCase();
    }
    return "und";
  }

  /**
   * Trims the string. If the field is empty after trimming, returns null instead. Note that this
   * only trims ASCII white-space.
   */
  public static String trimToNull(String originalStr) {
    if (originalStr == null) {
      return null;
    }
    String trimmedString = originalStr.trim();
    return (trimmedString.length() == 0) ? null : trimmedString;
  }

  /**
   * Throws an exception if the object is null, with a generic error message.
   */
  public static void checkNotNull(Object o) throws NullPointerException {
    checkNotNull(o, "This object should not be null.");
  }

  /**
   * Throws an exception if the object is null, with the error message supplied.
   */
  public static void checkNotNull(Object o, String message) throws NullPointerException {
    if (o == null) {
      throw new NullPointerException(message);
    }
  }

  /**
   * Joins input string with the given separator. If an input string is null,
   * it will be skipped.
   */
  public static String joinAndSkipNulls(String separator, String... strings) {
    StringBuilder sb = null;
    for (String s : strings) {
      if (s != null) {
        s = s.trim();
        if (s.length() > 0) {
          if (sb == null) {
            sb = new StringBuilder(s);
          } else {
            sb.append(separator).append(s);
          }
        }
      }
    }
    return sb == null ? null : sb.toString();
  }

  protected static Map<String, String> buildNameToKeyMap(String[] keys,
                                                         String[] names, String[] lnames) {
    if (keys == null) {
      return null;
    }

    Map<String, String> nameToKeyMap = new HashMap<String, String>();

    int len = keys.length;
    for (String k : keys) {
      nameToKeyMap.put(k.toLowerCase(), k);
    }
    if (names != null) {
      if (names.length != len) {
        throw new IllegalStateException("names (" + names.toString() + ") length"
            + " does not match keys (" + keys.toString() + ") length");
      }
      for (int i = 0; i < len; ++i) {
        nameToKeyMap.put(names[i].toLowerCase(), keys[i]);
      }
    }
    if (lnames != null) {
      if (lnames.length != len) {
        throw new IllegalStateException("lnames (" + lnames.toString() + ") length"
            + " does not match keys (" + keys.toString() + ") length");
      }
      for (int i = 0; i < len; ++i) {
        nameToKeyMap.put(lnames[i].toLowerCase(), keys[i]);
      }
    }

    return nameToKeyMap;
  }
}
