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

import junit.framework.TestCase;

/**
 * @author Lara Rennie
 */
public class UtilTest extends TestCase {

  public void testGetScriptCodeLatinScript() throws Exception {
    // Should recognise latin script in a variety of forms.
    assertEquals(Util.LATIN_SCRIPT, Util.getScriptCode("en"));
    assertEquals(Util.LATIN_SCRIPT, Util.getScriptCode("EN"));
    assertEquals(Util.LATIN_SCRIPT, Util.getScriptCode("zh-Latn"));
    assertEquals(Util.LATIN_SCRIPT, Util.getScriptCode("ja_LATN"));
    assertEquals(Util.LATIN_SCRIPT, Util.getScriptCode("ja_LATN-JP"));
    assertEquals(Util.LATIN_SCRIPT, Util.getScriptCode("ko-latn_JP"));
    // Other non-CJK scripts are also labelled as Latin.
    assertEquals(Util.LATIN_SCRIPT, Util.getScriptCode("ru"));
  }

  public void testGetScriptCodeCjkScript() throws Exception {
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("ko")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("KO")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("ja")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("ja-JP")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("zh-Hans")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("zh-Hans-CN")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("zh-Hant")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("zh-TW")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("zh_TW")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("ko")));
    assertFalse(Util.LATIN_SCRIPT.equals(Util.getScriptCode("ko_KR")));
  }
}
