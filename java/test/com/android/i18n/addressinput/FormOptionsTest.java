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
 * Test for building form options.
 */
public class FormOptionsTest extends TestCase {
  public void testRequiredField() throws Exception {
    FormOptions options = new FormOptions.Builder().required(AddressField.COUNTRY).build();
    assertTrue(options.isRequired(AddressField.COUNTRY));
    assertFalse(options.isRequired(AddressField.LOCALITY));
    assertTrue(options.getRequiredFields().contains(AddressField.COUNTRY));
    assertFalse(options.getRequiredFields().contains(AddressField.LOCALITY));
  }

  public void testReadonlyField() throws Exception {
    FormOptions options = new FormOptions.Builder().readonly(AddressField.COUNTRY).build();
    assertTrue(options.isReadonly(AddressField.COUNTRY));
    assertFalse(options.isReadonly(AddressField.LOCALITY));
  }

  public void testHiddenField() throws Exception {
    FormOptions options = new FormOptions.Builder().hide(AddressField.COUNTRY).build();
    assertTrue(options.isHidden(AddressField.COUNTRY));
    assertFalse(options.isHidden(AddressField.LOCALITY));
  }
}
