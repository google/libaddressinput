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

package com.google.i18n.addressinput.common;

import static com.google.common.truth.Truth.assertThat;
import static java.util.Arrays.asList;

import com.google.i18n.addressinput.common.LookupKey.ScriptType;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class FormatInterpreterTest {

  @SuppressWarnings("deprecation")
  @Test public void testIterateUsAddressFields() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    assertThat(formatInterpreter.getAddressFieldOrder(ScriptType.LOCAL, "US")).containsExactly(
        AddressField.RECIPIENT,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY,
        AddressField.ADMIN_AREA,
        AddressField.POSTAL_CODE)
        .inOrder();
  }

  /**
   * Tests that this works for the case of Vanuatu, since we have no country-specific formatting
   * data for that country. Should fall back to the default region.
   */
  @SuppressWarnings("deprecation")
  @Test public void testIterateVuAddressFields() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    assertThat(formatInterpreter.getAddressFieldOrder(ScriptType.LOCAL, "VU")).containsExactly(
        AddressField.RECIPIENT,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY)
        .inOrder();
  }

  @SuppressWarnings("deprecation")
  @Test public void testOverrideFieldOrder() {
    // Sorting code (CEDEX) is not in US address format and should be
    // neglected even if it is specified in customizeFieldOrder().
    FormatInterpreter myInterpreter = new FormatInterpreter(
        new FormOptions().setCustomFieldOrder("US",
            AddressField.ADMIN_AREA, AddressField.RECIPIENT,
            AddressField.SORTING_CODE, AddressField.POSTAL_CODE)
        .createSnapshot());

    assertThat(myInterpreter.getAddressFieldOrder(ScriptType.LOCAL, "US")).containsExactly(
        AddressField.ADMIN_AREA,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY,
        AddressField.RECIPIENT,
        AddressField.POSTAL_CODE)
        .inOrder();
  }

  @SuppressWarnings("deprecation")
  @Test public void testIterateTwLatinAddressFields() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    assertThat(formatInterpreter.getAddressFieldOrder(ScriptType.LATIN, "TW")).containsExactly(
        AddressField.RECIPIENT,
        AddressField.ORGANIZATION,
        AddressField.ADDRESS_LINE_1,
        AddressField.ADDRESS_LINE_2,
        AddressField.LOCALITY,
        AddressField.ADMIN_AREA,
        AddressField.POSTAL_CODE)
        .inOrder();
  }

  @Test public void testUsEnvelopeAddress() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    AddressData address = AddressData.builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mt View")
        .setAddress("1098 Alta Ave")
        .setPostalCode("94043")
        .build();
    assertThat(formatInterpreter.getEnvelopeAddress(address))
        .containsExactly("1098 Alta Ave", "Mt View, CA 94043").inOrder();
  }

  @Test public void testTwEnvelopeAddress() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    // To be in this order, the whole address should really be in Traditional Chinese - for
    // readability, only the neighbourhood and city are.
    AddressData address = AddressData.builder()
        .setCountry("TW")
        .setAdminArea("\u53F0\u5317\u5E02")  // Taipei city
        .setLocality("\u5927\u5B89\u5340")  // Da-an district
        .setAddress("Sec. 3 Hsin-yi Rd.")
        .setPostalCode("106")
        .setOrganization("Giant Bike Store")
        .setRecipient("Mr. Liu")
        .build();
    assertThat(formatInterpreter.getEnvelopeAddress(address)).containsExactly(
        "106",
        "\u53F0\u5317\u5E02\u5927\u5B89\u5340",  // Taipei city, Da-an district
        "Sec. 3 Hsin-yi Rd.",
        "Giant Bike Store",
        "Mr. Liu")
        .inOrder();
  }

  @Test public void testEnvelopeAddressIncompleteAddress() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    AddressData address = AddressData.builder()
        .setCountry("US")
        .setAdminArea("CA")
        // Locality is missing
        .setAddress("1098 Alta Ave")
        .setPostalCode("94043")
        .build();
    assertThat(formatInterpreter.getEnvelopeAddress(address))
        .containsExactly("1098 Alta Ave", "CA 94043").inOrder();
  }

  @Test public void testEnvelopeAddressEmptyAddress() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    AddressData address = AddressData.builder().setCountry("US").build();
    assertThat(formatInterpreter.getEnvelopeAddress(address)).isEmpty();
  }

  @Test public void testEnvelopeAddressLeadingPostPrefix() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    AddressData address = AddressData.builder()
        .setCountry("CH")
        .setPostalCode("8047")
        .setLocality("Herrliberg")
        .build();
    assertThat(formatInterpreter.getEnvelopeAddress(address))
        .containsExactly("CH-8047 Herrliberg").inOrder();
  }

  @Test public void testSvAddress() {
    FormatInterpreter formatInterpreter = new FormatInterpreter(new FormOptions().createSnapshot());
    AddressData svAddress = AddressData.builder()
        .setCountry("SV")
        .setAdminArea("Ahuachapán")
        .setLocality("Ahuachapán")
        .setAddressLines(asList("Some Street 12"))
        .build();
    assertThat(formatInterpreter.getEnvelopeAddress(svAddress))
        .containsExactly("Some Street 12", "Ahuachapán", "Ahuachapán").inOrder();

    AddressData svAddressWithPostCode =
        AddressData.builder(svAddress).setPostalCode("CP 2101").build();
    assertThat(formatInterpreter.getEnvelopeAddress(svAddressWithPostCode))
        .containsExactly("Some Street 12", "CP 2101-Ahuachapán", "Ahuachapán").inOrder();
  }
}
