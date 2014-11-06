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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Test cases for StandardAddressVerifier.
 */
public class StandardAddressVerifierTest extends TestCase {
  private static FieldVerifier createTestFieldVerifier() {
    return new FieldVerifier(new ClientData(new CacheData()));
  }

  private static AddressProblems verify(AddressData address) {
    StandardAddressVerifier verifier =
        new StandardAddressVerifier(createTestFieldVerifier(), StandardChecks.PROBLEM_MAP);
    AddressProblems problems = new AddressProblems();
    verifier.verify(address, problems);
    return problems;
  }

  public void testCustomProblemMapRespected() {
    AddressData usAddress = new AddressData.Builder().setCountry("US")
        .setAdminArea("Fake")
        .setAddress("1234 Somewhere")
        .setPostalCode("9402")
        .build();
    AddressProblems problems = verify(usAddress);
    assertFalse(problems.toString(), problems.isEmpty());

    assertEquals(AddressProblemType.INVALID_FORMAT,
        problems.getProblem(AddressField.POSTAL_CODE));
    assertEquals(AddressProblemType.UNKNOWN_VALUE,
        problems.getProblem(AddressField.ADMIN_AREA));
    // TODO: The standard address verifier fails to properly validate lower-level fields if a
    // higher-level field is of the wrong value. This is incorrect, and needs to be fixed.
    // assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
    //      problems.getProblem(AddressField.LOCALITY));

    // Now pass in a custom problem map.
    Map<AddressField, List<AddressProblemType>> customProblems =
        new HashMap<AddressField, List<AddressProblemType>>();
    StandardAddressVerifier emptyProblemVerifier = new StandardAddressVerifier(
        new FieldVerifier(new ClientData(new CacheData())),
        customProblems);
    problems.clear();
    emptyProblemVerifier.verify(usAddress, problems);
    // We aren't looking for any problems, so shouldn't find any.
    assertTrue(problems.toString(), problems.isEmpty());

    // Lastly try with a map that only looks for postal code problems.
    List<AddressProblemType> postalCodeProblems = new ArrayList<AddressProblemType>();
    postalCodeProblems.add(AddressProblemType.INVALID_FORMAT);
    postalCodeProblems.add(AddressProblemType.MISSING_REQUIRED_FIELD);
    customProblems.put(AddressField.POSTAL_CODE, postalCodeProblems);

    StandardAddressVerifier postalCodeProblemVerifier = new StandardAddressVerifier(
        new FieldVerifier(new ClientData(new CacheData())),
        customProblems);
    problems.clear();
    postalCodeProblemVerifier.verify(usAddress, problems);
    assertFalse(problems.toString(), problems.isEmpty());
    assertEquals(AddressProblemType.INVALID_FORMAT,
        problems.getProblem(AddressField.POSTAL_CODE));
    assertNull(problems.getProblem(AddressField.ADMIN_AREA));
  }

  public void testUnitedStatesOk() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mountain View")
        .setAddress("1234 Somewhere")
        .setPostalCode("94025")
        .build());
    assertTrue(problems.toString(), problems.isEmpty());  // no mismatch
  }

  public void testUnitedStatesZipMismatch() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mountain View")
        .setPostalCode("12345")
        .build());
    assertEquals(AddressProblemType.MISMATCHING_VALUE,
        problems.getProblem(AddressField.POSTAL_CODE));
  }

  public void testUnitedStatesNotOk() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality(null)
        .setDependentLocality("Foo Bar")
        .setPostalCode("12345")
        .build());
    assertEquals(AddressProblemType.MISMATCHING_VALUE,
        problems.getProblem(AddressField.POSTAL_CODE));
    assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
        problems.getProblem(AddressField.LOCALITY));
  }

  public void testChinaOk() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("CN")
        .setAdminArea("Beijing Shi")
        .setLocality("Xicheng Qu")
        .setAddress("Yitiao Lu")
        .setPostalCode("123456")
        .build());
    assertTrue(problems.toString(), problems.isEmpty());
  }

  public void testGermanAddress() {
    AddressData address = new AddressData.Builder()
        .setCountry("DE")
        .setLocality("Berlin")
        .setAddress("Huttenstr. 50")
        .setPostalCode("10553")
        .setOrganization("BMW AG Niederkassung Berlin")
        .setRecipient("Herr Diefendorf")
        .build();
    AddressProblems problems = verify(address);
    assertTrue(problems.toString(), problems.isEmpty());

    // Clones address but clears the city.
    address = new AddressData.Builder().set(address).setLocality(null).build();
    problems = verify(address);
    assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
        problems.getProblem(AddressField.LOCALITY));
  }

  public void testIrishAddress() {
    AddressData address = new AddressData.Builder()
        .setCountry("IE")
        .setLocality("Dublin")
        .setAdminArea("Co. Dublin")
        .setAddress("7424 118 Avenue NW")
        .setRecipient("Conan O'Brien")
        .build();
    AddressProblems problems = verify(address);
    assertTrue(problems.toString(), problems.isEmpty());

    // Clones address but clears county. This address should also be valid since county is not
    // required.
    address = new AddressData.Builder().set(address).setAdminArea(null).build();
    problems = verify(address);
    assertTrue(problems.toString(), problems.isEmpty());
  }

  public void testChinaPostalCodeBadFormat() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("CN")
        .setAdminArea("Beijing Shi")
        .setLocality("Xicheng Qu")
        .setPostalCode("12345")
        .build());
    assertEquals(AddressProblemType.INVALID_FORMAT,
        problems.getProblem(AddressField.POSTAL_CODE));
  }

  /**
   * If there is a postal code pattern for a certain country, and the input postal code is empty,
   * it should not be reported as bad postal code format. Whether empty postal code is ok should
   * be determined by checks for required fields.
   */
  public void testEmptyPostalCodeReportedAsGoodFormat() {
    // Chilean address has a postal code format pattern, but does not require postal code. The
    // following address is valid.
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("CL")
        .setAddressLine1("GUSTAVO LE PAIGE ST #159")
        .setAdminArea("Atacama")
        .setLocality("Alto del Carmen")
        .setPostalCode("")
        .build());
    assertTrue(problems.toString(), problems.isEmpty());
  }

  public void testMissingPostalCodeReportedAsBadFormat() {
    // Check for US addresses, which requires a postal code. The following address's postal code is
    // wrong because it is missing a required field, not because the postal code doesn't match the
    // administrative area.
    AddressProblems problems =
        verify(new AddressData.Builder().setCountry("US").setPostalCode("").build());
    assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
        problems.getProblem(AddressField.POSTAL_CODE));
  }

  public void testChinaTaiwanOk() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("CN")
        .setAdminArea("Taiwan")
        .setLocality("Taichung City")
        .setDependentLocality("Situn District")
        .setAddress("12345 Yitiao Lu")
        .setPostalCode("407")
        .build());
    assertTrue(problems.toString(), problems.isEmpty());
  }

  public void testChinaTaiwanUnknownDistrict() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("CN")
        .setAdminArea("Taiwan")
        .setLocality("Taichung City")
        .setDependentLocality("Foo Bar")
        .setPostalCode("400")
        .build());
    assertEquals(AddressProblemType.UNKNOWN_VALUE,
        problems.getProblem(AddressField.DEPENDENT_LOCALITY));
  }

  public void testStreetVerification() {
    // Missing street address
    AddressProblems problems = verify(new AddressData.Builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mountain View")
        .setPostalCode("94025")
        .build());
    assertEquals(AddressProblemType.MISSING_REQUIRED_FIELD,
        problems.getProblem(AddressField.STREET_ADDRESS));
  }

  public void testJapan() {
    AddressProblems problems =
        verify(new AddressData.Builder()
            .setRecipient("\u5BAE\u672C \u8302")  // SHIGERU_MIYAMOTO
            .setAddress("\u4E0A\u9CE5\u7FBD\u927E\u7ACB\u753A11\u756A\u5730")
            .setAdminArea("\u4eac\u90fd\u5e9c")  // Kyoto prefecture
            .setLocality("\u4EAC\u90FD\u5E02")  // Kyoto city
            .setCountry("JP")
            .setPostalCode("601-8501")
            .build());
    assertTrue(problems.toString(), problems.isEmpty());
  }

  public void testJapanLatin() {
    AddressProblems problems = verify(new AddressData.Builder()
        .setRecipient("Shigeru Miyamoto")
        .setAddress("11-1 Kamitoba-hokotate-cho")
        .setAdminArea("KYOTO")  // Kyoto prefecture
        .setLocality("Kyoto")  // Kyoto city
        .setLanguageCode("ja_Latn")
        .setCountry("JP")
        .setPostalCode("601-8501")
        .build());
    assertTrue(problems.toString(), problems.isEmpty());
  }
}
