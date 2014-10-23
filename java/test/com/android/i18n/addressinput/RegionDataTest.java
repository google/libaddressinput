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
 * Small unit tests for the RegionData class.
 */
public class RegionDataTest extends TestCase {
  public void testBuilder() throws Exception {
    RegionData data = new RegionData.Builder().setKey("CA").setName("California").build();
    assertEquals("CA", data.getKey());
    assertEquals("California", data.getName());
    assertTrue(data.isValidName("CA"));
    // Should match either the key or the name.
    assertTrue(data.isValidName("California"));
    // Matching should be case-insensitive.
    assertTrue(data.isValidName("ca"));
    assertFalse(data.isValidName("Cat"));
  }

  public void testBuilderNoName() throws Exception {
    RegionData data = new RegionData.Builder().setKey("CA").build();
    assertEquals("CA", data.getKey());
    assertEquals(null, data.getName());
  }

  public void testBuilderWhitespaceName() throws Exception {
    RegionData data = new RegionData.Builder().setKey("CA").setName("  ").build();
    assertEquals("CA", data.getKey());
    assertEquals(null, data.getName());
    assertEquals("CA", data.getDisplayName());
  }
}
