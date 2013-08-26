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

import com.android.i18n.addressinput.testing.AddressDataMapLoader;

import junit.framework.TestCase;

/**
 * Spot check the standard data set for various cases of interest. This is not an exhaustive test.
 */
public class FieldVerifierTest extends TestCase {

    private static final StandardAddressVerifier VERIFIER =
            new StandardAddressVerifier(new FieldVerifier(
                    new AddressVerificationData(AddressDataMapLoader.DATA)));

    private AddressProblems problems = new AddressProblems();

    @Override
    protected void setUp() {
        problems.clear();
    }

    public void testUnitedStatesOk() {
        AddressData addr = new AddressData.Builder().setCountry("US")
                                                    .setAdminArea("CA")
                                                    .setLocality("Mountain View")
                                                    .setAddress("1234 Somewhere")
                                                    .setPostalCode("94025").build();
        VERIFIER.verify(addr, problems);
        assertTrue(problems.toString(), problems.isEmpty());  // no mismatch
    }

    public void testUnitedStatesZipMismatch() {
        AddressData addr = new AddressData.Builder().setCountry("US")
                                                    .setAdminArea("CA")
                                                    .setLocality("Mountain View")
                                                    .setPostalCode("12345").build();
        VERIFIER.verify(addr, problems);

        assertEquals(AddressProblemType.MISMATCHING_VALUE,
                     problems.getProblem(AddressField.POSTAL_CODE));
    }

    public void testUnitedStatesNotOk() {
        AddressData addr = new AddressData.Builder().setCountry("US")
                                                    .setAdminArea("CA")
                                                    .setLocality(null)
                                                    .setDependentLocality("Foo Bar")
                                                    .setPostalCode("12345").build();
        VERIFIER.verify(addr, problems);

        assertEquals(AddressProblemType.MISMATCHING_VALUE,
                     problems.getProblem(AddressField.POSTAL_CODE));
        assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
                     problems.getProblem(AddressField.LOCALITY));
    }

    public void testChinaOk() {
        AddressData addr = new AddressData.Builder().setCountry("CN")
                                                    .setAdminArea("Beijing Shi")
                                                    .setLocality("Xicheng Qu")
                                                    .setAddress("Yitiao Lu")
                                                    .setPostalCode("123456").build();
        VERIFIER.verify(addr, problems);
        assertTrue(problems.isEmpty());
    }

    public void testGermanAddress() {
        AddressData addr = new AddressData.Builder().setCountry("DE")
                                                    .setLocality("Berlin")
                                                    .setAddress("Huttenstr. 50")
                                                    .setPostalCode("10553")
                                                    .setOrganization("BMW AG Niederkassung Berlin")
                                                    .setRecipient("Herr Diefendorf").build();

        VERIFIER.verify(addr, problems);
        assertTrue(problems.isEmpty());

        // Clones address but leave city empty.
        addr = new AddressData.Builder().set(addr).setLocality(null).build();

        VERIFIER.verify(addr, problems);
        assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
                     problems.getProblem(AddressField.LOCALITY));
    }

    public void testIrishAddress() {
        AddressData addr = new AddressData.Builder().setCountry("IE")
                                                    .setLocality("Dublin")
                                                    .setAdminArea("Co. Dublin")
                                                    .setAddress("7424 118 Avenue NW")
                                                    .setRecipient("Conan O'Brien").build();

        VERIFIER.verify(addr, problems);
        assertTrue(problems.toString(), problems.isEmpty());

        // Clones address but leave county empty. This address should be valid
        // since county is not required.
        addr = new AddressData.Builder().set(addr).setAdminArea(null).build();

        VERIFIER.verify(addr, problems);
        assertTrue(problems.toString(), problems.isEmpty());
    }

    public void testChinaPostalCodeBadFormat() {
        AddressData addr = new AddressData.Builder().setCountry("CN")
                                                    .setAdminArea("Beijing Shi")
                                                    .setLocality("Xicheng Qu")
                                                    .setPostalCode("12345").build();
        VERIFIER.verify(addr, problems);

        assertEquals(AddressProblemType.UNRECOGNIZED_FORMAT,
                     problems.getProblem(AddressField.POSTAL_CODE));
    }

    /**
     * If there is a postal code pattern for a certain country, and the input postal code is empty,
     * it should not be reported as bad postal code format. Whether empty postal code is ok should
     * be determined by checks for required fields.
     */
    public void testEmptyPostalCodeReportedAsGoodFormat() {
        // Chilean address has a postal code format pattern, but does not require
        // postal code. The following address is valid.
        AddressData addr = new AddressData.Builder().setCountry("CL")
                                                    .setAddressLine1("GUSTAVO LE PAIGE ST #159")
                                                    .setAdminArea("Atacama")
                                                    .setLocality("San Pedro")
                                                    .setPostalCode("")
                                                    .build();
        VERIFIER.verify(addr, problems);
        assertTrue(problems.toString(), problems.isEmpty());

        problems.clear();

        // Now check for US addresses, which require a postal code. The following
        // address's postal code is wrong because it is missing a required field, not
        // because it doesn't match the expected postal code pattern.
        addr = new AddressData.Builder().setCountry("US").setPostalCode("").build();
        problems.clear();
        VERIFIER.verify(addr, problems);

        assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
                     problems.getProblem(AddressField.POSTAL_CODE));
    }

    public void testChinaTaiwanOk() {
        AddressData addr = new AddressData.Builder().setCountry("CN")
                                                    .setAdminArea("Taiwan")
                                                    .setLocality("Taichung City")
                                                    .setDependentLocality("Situn District")
                                                    .setAddress("12345 Yitiao Lu")
                                                    .setPostalCode("407").build();
        VERIFIER.verify(addr, problems);
        assertTrue(problems.isEmpty());
    }

    public void testChinaTaiwanUnknownDistrict() {
        AddressData addr = new AddressData.Builder().setCountry("CN")
                                                    .setAdminArea("Taiwan")
                                                    .setLocality("Taichung City")
                                                    .setDependentLocality("Foo Bar")
                                                    .setPostalCode("400").build();
        VERIFIER.verify(addr, problems);

        assertEquals(AddressProblemType.UNKNOWN_VALUE,
                     problems.getProblem(AddressField.DEPENDENT_LOCALITY));
    }

    public void testStreetVerification() {
        // Missing street address
        AddressData addr = new AddressData.Builder().setCountry("US")
                                                    .setAdminArea("CA")
                                                    .setLocality("Mountain View")
                                                    .setPostalCode("94025").build();

        assertNull(addr.getAddressLine1());
        assertNull(addr.getAddressLine2());

        VERIFIER.verify(addr, problems);

        assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
                     problems.getProblem(AddressField.STREET_ADDRESS));
    }

    // Tests The Bahamas' address
    public void failingtestBahamas() {
        final AddressData address =
                new AddressData.Builder().setAddress("Abaco Beach Resort & Boat Habour")
                                         .setLocality("Treasure Cay")
                                         .setAdminArea("Abaco")
                                         .setCountry("BS").build();
        VERIFIER.verify(address, problems);
        assertTrue(problems.isEmpty());
    }

    public void testJapan() {
        // Added AdminArea since address verification can't infer it from Kyoto City
        // Commented out dependent locality since we don't have the data for this and in fact say
        // that it shouldn't be used for Japan.
        // TODO: support inference of higher levels from lower ones
        final AddressData address = new AddressData.Builder()
                .setRecipient("\u5BAE\u672C \u8302")  // SHIGERU_MIYAMOTO
                .setAddress("\u4E0A\u9CE5\u7FBD\u927E\u7ACB\u753A11\u756A\u5730")
                .setAdminArea("\u4eac\u90fd\u5e9c")  // Kyoto prefecture, added
                .setLocality("\u4EAC\u90FD\u5E02")  // Kyoto city
                // .setDependentLocality("\u5357\u533A")
                .setCountry("JP")
                .setPostalCode("601-8501").build();
        VERIFIER.verify(address, problems);
        assertTrue(problems.toString(), problems.isEmpty());
    }

    public void testJapanLatin() {
        // added AdminArea since address verification can't infer it from Kyoto City
        // commented out dependent locality since address verification doesn't use it
        final AddressData address = new AddressData.Builder()
            .setRecipient("Shigeru Miyamoto")  // SHIGERU_MIYAMOTO_ENGLISH
            .setAddress("11-1 Kamitoba-hokotate-cho")
            .setAdminArea("KYOTO")  // added
            .setLocality("Kyoto")
            // .setDependentLocality("Minami-ku")
            .setLanguageCode("ja_Latn")
            .setCountry("JP")
            .setPostalCode("601-8501").build();
        VERIFIER.verify(address, problems);
        assertTrue(problems.isEmpty());
    }

    public void testJapanLatinInvalidAdmin() {
        final AddressData address = new AddressData.Builder()
                .setRecipient("Shigeru Miyamoto")  // SHIGERU_MIYAMOTO_ENGLISH
                .setAddress("11-1 Kamitoba-hokotate-cho")
                .setAdminArea("Fake Admin")
                .setLocality("Kyoto")
                .setLanguageCode("ja_Latn")
                .setCountry("JP")
                .setPostalCode("601-8501").build();
        VERIFIER.verify(address, problems);
        assertFalse(problems.isEmpty());
        assertEquals(AddressProblemType.UNKNOWN_VALUE,
                     problems.getProblem(AddressField.ADMIN_AREA));
    }

    public void testCanadaMixedCasePostcode() {
      final AddressData address = new AddressData.Builder()
              .setRecipient("Joe Bloggs")
              .setAddress("11 East St")
              .setLocality("Montreal")
              .setAdminArea("Quebec")
              .setCountry("CA")
              .setPostalCode("H2b 2y5").build();
      VERIFIER.verify(address, problems);
      assertTrue(problems.isEmpty());
  }
}
