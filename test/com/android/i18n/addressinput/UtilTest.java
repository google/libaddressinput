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

import java.util.Locale;

import junit.framework.TestCase;

/**
 * Tests for util functions.
 */
public class UtilTest extends TestCase {

  public void testIsExplicitLatinScript() throws Exception {
    // Should recognise latin script in a variety of forms.
    assertTrue(Util.isExplicitLatinScript("zh-Latn"));
    assertTrue(Util.isExplicitLatinScript("ja_LATN"));
    assertTrue(Util.isExplicitLatinScript("und_LATN"));
    assertTrue(Util.isExplicitLatinScript("ja_LATN-JP"));
    assertTrue(Util.isExplicitLatinScript("ko-latn_JP"));
  }

  public void testIsExplicitLatinScriptNonLatin() throws Exception {
    assertFalse(Util.isExplicitLatinScript("ko"));
    assertFalse(Util.isExplicitLatinScript("KO"));
    assertFalse(Util.isExplicitLatinScript("ja"));
    assertFalse(Util.isExplicitLatinScript("ja-JP"));
    assertFalse(Util.isExplicitLatinScript("zh-Hans"));
    assertFalse(Util.isExplicitLatinScript("zh-Hans-CN"));
    assertFalse(Util.isExplicitLatinScript("zh-Hant"));
    assertFalse(Util.isExplicitLatinScript("zh-TW"));
    assertFalse(Util.isExplicitLatinScript("zh_TW"));
    assertFalse(Util.isExplicitLatinScript("ko"));
    assertFalse(Util.isExplicitLatinScript("ko_KR"));
    assertFalse(Util.isExplicitLatinScript("en"));
    assertFalse(Util.isExplicitLatinScript("EN"));
    assertFalse(Util.isExplicitLatinScript("ru"));
  }

  public void testGetLanguageSubtag() throws Exception {
    assertEquals("zh", Util.getLanguageSubtag("zh-Latn"));
    assertEquals("ja", Util.getLanguageSubtag("ja_LATN"));
    assertEquals("und", Util.getLanguageSubtag("und_LATN"));
    assertEquals("ja", Util.getLanguageSubtag("ja_LATN-JP"));
    assertEquals("ko", Util.getLanguageSubtag("ko"));
    assertEquals("ko", Util.getLanguageSubtag("KO"));
    assertEquals("ko", Util.getLanguageSubtag("ko-KR"));
    assertEquals("ko", Util.getLanguageSubtag("ko_kr"));
    assertEquals("und", Util.getLanguageSubtag("Not a language"));
  }

  public void testTrimToNull() throws Exception {
    assertEquals("Trimmed String", Util.trimToNull("  Trimmed String   "));
    assertEquals("Trimmed String", Util.trimToNull("  Trimmed String"));
    assertEquals("Trimmed String", Util.trimToNull("Trimmed String"));
    assertEquals(null, Util.trimToNull("  "));
    assertEquals(null, Util.trimToNull(null));
  }

  public void testJoinAndSkipNulls() throws Exception {
    String first = "String 1";
    String second = "String 2";
    String expectedString = "String 1-String 2";
    String nullString = null;
    assertEquals(expectedString, Util.joinAndSkipNulls("-", first, second));
    assertEquals(expectedString, Util.joinAndSkipNulls("-", first, second, nullString));
    assertEquals(expectedString, Util.joinAndSkipNulls("-", first, nullString, second));
    assertEquals(expectedString, Util.joinAndSkipNulls("-", first, nullString, " ", second));
    assertEquals(first, Util.joinAndSkipNulls("-", first, nullString));
    assertEquals(first, Util.joinAndSkipNulls("-", nullString, first));

    assertEquals(null, Util.joinAndSkipNulls("-", nullString));
    assertEquals(null, Util.joinAndSkipNulls("-", nullString, nullString));
    assertEquals(null, Util.joinAndSkipNulls("-", nullString, "", nullString));
  }

  public void testGetWidgetCompatibleLanguageCodeCjkCountry() throws Exception {
    Locale canadianFrench = new Locale("fr", "CA");
    // Latin language, CJK country. Need explicit latin tag, and country should be retained.
    assertEquals("fr_latn_CA", Util.getWidgetCompatibleLanguageCode(canadianFrench, "CN"));
    Locale canadianFrenchUpper = new Locale("FR", "CA");
    // Test that the locale returns the same language code, regardless of the case of the initial
    // input.
    assertEquals("fr_latn_CA", Util.getWidgetCompatibleLanguageCode(canadianFrenchUpper, "CN"));
    // No country in the Locale language.
    assertEquals("fr_latn", Util.getWidgetCompatibleLanguageCode(Locale.FRENCH, "CN"));
    // CJK language - should be unaltered.
    assertEquals(Locale.KOREAN.toString(),
                 Util.getWidgetCompatibleLanguageCode(Locale.KOREAN, "CN"));
    Locale chineseChina = new Locale("zh", "CN");
    assertEquals("zh_CN",
                 Util.getWidgetCompatibleLanguageCode(chineseChina, "CN"));
  }

  public void testGetWidgetCompatibleLanguageCodeNonCjkCountry() throws Exception {
    // Nothing should be changed for non-CJK countries, since their form layout is the same
    // regardless of language.
    Locale canadianFrench = new Locale("fr", "CA");
    assertEquals("fr_CA", Util.getWidgetCompatibleLanguageCode(canadianFrench, "US"));
    // No country in the Locale language.
    assertEquals(Locale.FRENCH.toString(),
                 Util.getWidgetCompatibleLanguageCode(Locale.FRENCH, "US"));
    // CJK language - should be unaltered too.
    assertEquals(Locale.KOREAN.toString(),
                 Util.getWidgetCompatibleLanguageCode(Locale.KOREAN, "US"));
  }
}
