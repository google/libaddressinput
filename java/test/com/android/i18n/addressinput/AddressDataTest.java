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

import java.util.Arrays;
import java.util.List;

/**
 * Tests for the AddressData class.
 */
public class AddressDataTest extends TestCase {
  private static final String ADDRESS_LINE = "First address line";

  public void testAddressLineSimple() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("First line")
        .setAddressLine2("Second line")
        .build();
    assertEquals("First line", address.getAddressLine1());
    assertEquals("Second line", address.getAddressLine2());
  }

  public void testManyAddressLines() {
    List<String> lines = Arrays.asList(new String[] {
        "First line", "Second line", "Third line", "Fourth line", "Last line"});
    AddressData address = new AddressData.Builder()
        .setAddressLines(lines)
        .build();
    assertEquals(lines, address.getAddressLines());

    // When accessing via specific line getters, any lines after 2 are concatenated to the second.
    assertEquals("First line", address.getAddressLine1());
    assertEquals("Second line, Third line, Fourth line, Last line", address.getAddressLine2());
  }

  public void testSetAddressLine() {
    AddressData.Builder builder = new AddressData.Builder();
    builder = builder.setAddress("\n " + ADDRESS_LINE);
    AddressData ad = builder.build();
    assertEquals(ADDRESS_LINE, ad.getAddressLine1());
    assertNull(ad.getAddressLine2());
  }

  public void testAddressLineNormalisationTrimsWhitespace() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("\t  Line with whitespace around it   ")
        .build();
    assertEquals("Line with whitespace around it", address.getAddressLine1());
    assertNull(address.getAddressLine2());
  }

  public void testAddressLineNormalisationSplitsOnNewline() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("First line\nSecond line").build();
    assertEquals("First line", address.getAddressLine1());
    assertEquals("Second line", address.getAddressLine2());
  }

  public void testAddressLineNormalisationExcludesNull() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1(null)
        .setAddressLine2("First non-null line")
        .build();
    assertEquals("First non-null line", address.getAddressLine1());
    assertNull(address.getAddressLine2());
  }

  public void testAddressLineNormalisationExcludesEmptyOrWhitespace() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("")
        .setAddressLine2("First non-empty line")
        .build();
    assertEquals("First non-empty line", address.getAddressLine1());
    assertNull(address.getAddressLine2());
  }

  public void testAddressLineNormalisationComplex() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("  \n\t \t\n")
        .setAddressLine2("   \n   First non-empty line   \n   \t ")
        .build();
    assertEquals("First non-empty line", address.getAddressLine1());
    assertNull(address.getAddressLine2());
  }

  public void testAddressLineNormalisationManyEmbeddedLines() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("\nFirst line  \nSecond line  ")
        .setAddressLine2("\n  Third line\n Last line \t ")
        .build();
    assertEquals("First line", address.getAddressLine1());
    assertEquals("Second line, Third line, Last line", address.getAddressLine2());
  }

  public void testBuilderSplitsLinesLazily() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("First line\nSecond line")
        // The first address line hasn't been split yet, so resetting the 2nd line does nothing.
        .setAddressLine2(null)
        .build();
    assertEquals("First line", address.getAddressLine1());
    assertEquals("Second line", address.getAddressLine2());
  }

  public void testBuilderDoesNotReindexFieldsOnRemoval() {
    AddressData address = new AddressData.Builder()
        .setAddressLine1("First line (should be removed)")
        .setAddressLine2("Second line (should be removed)")
        // Removing the first line does not reindex the 2nd line to be the first line.
        .setAddressLine1(null)
        .setAddressLine2("Only line")
        .build();
    assertEquals("Only line", address.getAddressLine1());
    assertNull(address.getAddressLine2());
  }

  public void testNoAdminArea() {
    AddressData address = new AddressData.Builder().build();
    assertNull(address.getAdministrativeArea());
  }

  public void testSetLanguageCode() throws Exception {
    AddressData address = new AddressData.Builder()
        .setCountry("TW")
        .setAdminArea("\u53F0\u5317\u5E02")  // Taipei City
        .setLocality("\u5927\u5B89\u5340")  // Da-an District
        .build();
    // Actually, this address is not in Latin-script Chinese, but we are just testing that the
    // language we set is the same as the one we get back.
    address = new AddressData.Builder(address).setLanguageCode("zh-latn").build();
    assertEquals("zh-latn", address.getLanguageCode());
  }
}
