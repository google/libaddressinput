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
 * Tests for the AddressData class.
 */
public class AddressDataTest extends TestCase {
    private static final String ADDRESS_LINE = "First address line";

    public void testSetAddressLine() {
        AddressData.Builder builder = new AddressData.Builder();
        builder = builder.setAddress("\n " + ADDRESS_LINE);
        AddressData ad = builder.build();
        assertEquals(ADDRESS_LINE, ad.getAddressLine1());
        assertEquals(null, ad.getAddressLine2());
    }

    public void testAddressLineNormalisation() {
        AddressData address = new AddressData.Builder().setAddressLine1(null)
                                                       .setAddressLine2(ADDRESS_LINE).build();
        AddressData copiedAddress = new AddressData.Builder(address).build();
        assertEquals(ADDRESS_LINE, copiedAddress.getAddressLine1());
        assertEquals(null, copiedAddress.getAddressLine2());
    }

    public void testAddressLineNormalisationWithNewLineCharacters() {
        AddressData address =
            new AddressData.Builder().setAddressLine1(ADDRESS_LINE + "\n" + ADDRESS_LINE).build();
        AddressData copiedAddress = new AddressData.Builder(address).build();
        assertEquals(ADDRESS_LINE, copiedAddress.getAddressLine1());
        assertEquals(ADDRESS_LINE, copiedAddress.getAddressLine2());
    }

    public void testNoAdminArea() {
        AddressData address = new AddressData.Builder().build();
        assertEquals(null, address.getAdministrativeArea());
    }

    public void testSetLanguageCode() throws Exception {
        AddressData address = new AddressData.Builder().setCountry("TW")
                                                       // Taipei City
                                                       .setAdminArea("\u53F0\u5317\u5E02")
                                                       // Da-an District
                                                       .setLocality("\u5927\u5B89\u5340")
                                                       .build();
        address = new AddressData.Builder(address).setLanguageCode("zh-latn").build();
        assertEquals("zh-latn", address.getLanguageCode());
    }
}
