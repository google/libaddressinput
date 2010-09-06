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

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Utility functions used by the address widget.
 *
 * @author Lara Rennie
 */
public class Util {
  public static final String LATIN_SCRIPT = "Latn";

  // Only used internally.
  private static final String CHINESE_SCRIPT = "Hans";
  private static final String KOREAN_SCRIPT = "Kore";
  private static final String JAPANESE_SCRIPT = "Jpan";
  // These are in upper-case, since we convert the language code to upper case before doing
  // string comparison.
  private static final String CHINESE_LANGUAGE = "ZH";
  private static final String JAPANESE_LANGUAGE = "JA";
  private static final String KOREAN_LANGUAGE = "KO";

  // Cannot instantiate this class - private constructor.
  private Util() {}

  /**
   * Gets the script code for a particular language. This is a somewhat hacky replacement for ICU's
   * class that does this properly. For our purposes, we only want to know if the address is in a
   * CJK script or not, since that affects address formatting. We assume that the languageCode is
   * well-formed and first search to see if there is a script code specified. If not, then we assume
   * Chinese, Japanese and Korean are in their default scripts, and other languages are in Latin
   * script.
   */
  public static String getScriptCode(String languageCode) {
    // Convert to upper-case for easier comparison.
    languageCode = languageCode.toUpperCase();
    // Check to see if the language code contains a script modifier.
    final Pattern languageCodePattern = Pattern.compile("\\w{2}[-_](\\w{4})");
    Matcher m = languageCodePattern.matcher(languageCode);
    if (m.lookingAt()) {
      String script = m.group(1);
      if (script.equals(LATIN_SCRIPT.toUpperCase())) {
        return LATIN_SCRIPT;
      }
    }
    // If the script was not explicitly specified as Latn, we ignore the script information and read
    // the language tag instead. This would break for cases such as zh-Cyrl, but this is rare enough
    // that we are not going to worry about it for now.
    if (languageCode.startsWith(CHINESE_LANGUAGE)) {
      // We don't distinguish between simplified and traditional Chinese here.
      return CHINESE_SCRIPT;
    } else if (languageCode.startsWith(JAPANESE_LANGUAGE)) {
      return JAPANESE_SCRIPT;
    } else if (languageCode.startsWith(KOREAN_LANGUAGE)) {
      return KOREAN_SCRIPT;
    }
    // All Indic, Arabic and other scripts will be mislabelled by this function, but since we only
    // want to distinguish between CJK and non-CJK, this is ok.
    return LATIN_SCRIPT;
  }
}
