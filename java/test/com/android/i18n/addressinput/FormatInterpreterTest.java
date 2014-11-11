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

import com.android.i18n.addressinput.LookupKey.ScriptType;

import junit.framework.TestCase;

import java.util.ArrayList;
import java.util.List;

/**
 * Tests for {@link FormatInterpreter}.
 */
public class FormatInterpreterTest extends TestCase {
  private static final AddressData US_CA_ADDRESS;
  private static final AddressData TW_ADDRESS;

  private FormatInterpreter formatInterpreter;

  static {
    US_CA_ADDRESS = new AddressData.Builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mt View")
        .setAddressLine1("1098 Alta Ave")
        .setPostalCode("94043")
        .build();

    TW_ADDRESS = new AddressData.Builder()
        .setCountry("TW")
        .setAdminArea("\u53F0\u5317\u5E02")  // Taipei city
        .setLocality("\u5927\u5B89\u5340")  // Da-an district
        .setAddressLine1("Sec. 3 Hsin-yi Rd.")
        .setPostalCode("106")
        .setOrganization("Giant Bike Store")
        .setRecipient("Mr. Liu")
        .build();
  }

  @Override
  public void setUp() {
    formatInterpreter = new FormatInterpreter(new FormOptions.Builder().build());
  }

  public void testIterateUsAddressFields() {
    AddressField[] format = {
        AddressField.RECIPIENT,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY,
        AddressField.ADMIN_AREA,
        AddressField.POSTAL_CODE};

    int currIndex = 0;
    for (AddressField field : formatInterpreter.getAddressFieldOrder(ScriptType.LOCAL, "US")) {
      assertEquals("index " + currIndex + " should have matched",
          format[currIndex].getChar(), field.getChar());
      currIndex++;
    }
  }

  /**
   * Tests that this works for the case of Vanuatu, since we have no country-specific formatting
   * data for that country. Should fall back to the default region.
   */
  public void testIterateVuAddressFields() {
    AddressField[] format = {
        AddressField.RECIPIENT,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY,
    };

    int currIndex = 0;
    for (AddressField field : formatInterpreter.getAddressFieldOrder(ScriptType.LOCAL, "VU")) {
      assertEquals("index " + currIndex + " should have matched",
          format[currIndex].getChar(), field.getChar());
      currIndex++;
    }
  }

  public void testOverrideFieldOrder() {
    AddressField[] expectedOrder = {
        AddressField.ADMIN_AREA,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY,
        AddressField.RECIPIENT,
        AddressField.POSTAL_CODE};

    FormatInterpreter myInterpreter = new FormatInterpreter(
        new FormOptions.Builder().customizeFieldOrder("US",
            AddressField.ADMIN_AREA, AddressField.RECIPIENT,
            AddressField.SORTING_CODE, AddressField.POSTAL_CODE)
        .build());

    int currIndex = 0;
    for (AddressField field : myInterpreter.getAddressFieldOrder(ScriptType.LOCAL, "US")) {
      assertEquals("Wrong field order for US on index " + currIndex + " of address fields.",
          expectedOrder[currIndex], field);

      // Sorting code (CEDEX) is not in US address format and should be
      // neglected even if it is specified in customizeFieldOrder().
      assertNotSame(AddressField.SORTING_CODE, field);
      currIndex++;
    }
  }

  public void testIterateTwLatinAddressFields() {
    AddressField[] format = {
        AddressField.RECIPIENT,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY,
        AddressField.ADMIN_AREA,
        AddressField.POSTAL_CODE};

    int currIndex = 0;
    for (AddressField field : formatInterpreter.getAddressFieldOrder(ScriptType.LATIN, "TW")) {
      assertEquals("Unexpected field order -- mismatched on index " + currIndex,
          format[currIndex].getChar(), field.getChar());
      currIndex++;
    }
  }

  public void testUsEnvelopeAddress() {
    List<String> expected = new ArrayList<String>();
    expected.add("1098 Alta Ave");
    expected.add("Mt View, CA 94043");

    List<String> real = formatInterpreter.getEnvelopeAddress(US_CA_ADDRESS);
    assertEquals(expected, real);
  }

  public void testTwEnvelopeAddress() {
    // To be in this order, the whole address should really be in Traditional Chinese - for
    // readability, only the neighbourhood and city are.
    List<String> expected = new ArrayList<String>();
    expected.add("106");
    expected.add("\u53F0\u5317\u5E02\u5927\u5B89\u5340");  // Taipei city, Da-an district
    expected.add("Sec. 3 Hsin-yi Rd.");
    expected.add("Giant Bike Store");
    expected.add("Mr. Liu");

    List<String> real = formatInterpreter.getEnvelopeAddress(TW_ADDRESS);

    assertEquals(expected, real);
  }

  public void testEnvelopeAddressIncompleteAddress() {
    List<String> expected = new ArrayList<String>();
    expected.add("1098 Alta Ave");
    expected.add("CA 94043");

    AddressData address =
        new AddressData.Builder().set(US_CA_ADDRESS).set(AddressField.LOCALITY, null).build();

    List<String> real = formatInterpreter.getEnvelopeAddress(address);
    assertEquals(expected, real);
  }

  public void testEnvelopeAddressEmptyAddress() {
    List<String> expected = new ArrayList<String>();
    AddressData address = new AddressData.Builder().setCountry("US").build();

    List<String> real = formatInterpreter.getEnvelopeAddress(address);
    assertEquals(expected, real);
  }

  public void testEnvelopeAddressLeadingPostPrefix() {
    List<String> expected = new ArrayList<String>();
    expected.add("CH-8047 Herrliberg");
    AddressData address = new AddressData.Builder()
        .setCountry("CH")
        .setPostalCode("8047")
        .setLocality("Herrliberg")
        .build();

    List<String> real = formatInterpreter.getEnvelopeAddress(address);
    assertEquals(expected, real);
  }

  public void testSvAddress() {
    AddressData svAddress = new AddressData.Builder()
        .setCountry("SV")
        .setAdminArea("Ahuachapán")
        .setLocality("Ahuachapán")
        .setAddressLine1("Some Street 12")
        .build();

    List<String> expected = new ArrayList<String>();
    expected.add("Some Street 12");
    expected.add("Ahuachapán");
    expected.add("Ahuachapán");

    List<String> real = formatInterpreter.getEnvelopeAddress(svAddress);
    assertEquals(expected, real);

    AddressData svAddressWithPostCode =
        new AddressData.Builder(svAddress).setPostalCode("CP 2101").build();

    expected = new ArrayList<String>();
    expected.add("Some Street 12");
    expected.add("CP 2101-Ahuachapán");
    expected.add("Ahuachapán");

    real = formatInterpreter.getEnvelopeAddress(svAddressWithPostCode);
    assertEquals(expected, real);
  }
}
