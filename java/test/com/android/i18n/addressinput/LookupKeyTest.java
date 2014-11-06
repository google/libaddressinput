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

import com.android.i18n.addressinput.LookupKey.KeyType;

import junit.framework.TestCase;

import java.util.HashMap;
import java.util.Map;

/**
 * Unit tests for the LookupKey class.
 */
public class LookupKeyTest extends TestCase {
  private static final String ROOT_KEY = "data";
  private static final String ROOT_EXAMPLE_KEY = "examples";
  private static final String US_KEY = "data/US";
  private static final String HK_NEW_TERRITORIES_KEY_EN = "data/HK/New Territories--en";
  private static final String HK_DISTRICT_KEY_EN = "data/HK/New Territories/District--en";
  private static final String CALIFORNIA_KEY = "data/US/CA";
  private static final String EXAMPLE_LOCAL_US_KEY = "examples/US/local/_default";

  // Data key for Da-an District, Taipei Taiwan
  private static final String TW_KEY = "data/TW/\u53F0\u5317\u5E02/\u5927\u5B89\u5340";

  // Example key for TW's address (local script)
  private static final String TW_EXAMPLE_LOCAL_KEY = "examples/TW/local/_default";

  // Example key for TW's address (latin script)
  private static final String TW_EXAMPLE_LATIN_KEY = "examples/TW/latin/_default";

  private static final String RANDOM_KEY = "sdfIisooIFOOBAR";
  private static final String RANDOM_COUNTRY_KEY = "data/asIOSDxcowW";

  public void testRootKey() {
    LookupKey key = new LookupKey.Builder(KeyType.DATA).build();
    assertEquals(ROOT_KEY, key.toString());

    LookupKey key2 = new LookupKey.Builder(key.toString()).build();
    assertEquals(ROOT_KEY, key2.toString());
  }

  public void testLanguageKeysRoundTrip() {
    LookupKey key = new LookupKey.Builder(HK_NEW_TERRITORIES_KEY_EN).build();
    assertEquals(HK_NEW_TERRITORIES_KEY_EN, key.toString());

    LookupKey districtKey = new LookupKey.Builder(HK_DISTRICT_KEY_EN).build();
    assertEquals(HK_DISTRICT_KEY_EN, districtKey.toString());
  }

  public void testDataKeys() {
    LookupKey key = new LookupKey.Builder(US_KEY).build();
    assertEquals(US_KEY, key.toString());

    LookupKey key2 = new LookupKey.Builder(CALIFORNIA_KEY).build();
    assertEquals(CALIFORNIA_KEY, key2.toString());
  }

  public void testExampleRootKeys() {
    LookupKey key = new LookupKey.Builder(KeyType.EXAMPLES).build();
    assertEquals(ROOT_EXAMPLE_KEY, key.toString());
  }

  public void testExampleKeys() {
    AddressData address = new AddressData.Builder().setCountry("US").setLanguageCode("en").build();

    LookupKey key = new LookupKey.Builder(KeyType.EXAMPLES).setAddressData(address).build();
    assertEquals(EXAMPLE_LOCAL_US_KEY, key.toString());

    key = new LookupKey.Builder(EXAMPLE_LOCAL_US_KEY).build();
    assertEquals(EXAMPLE_LOCAL_US_KEY, key.toString());
  }

  public void testKeyWithWrongScriptType() {
    String wrongScript = "examples/US/asdfasdfasdf/_default";
    try {
      new LookupKey.Builder(wrongScript).build();
      fail("should fail since the script type is wrong");
    } catch (RuntimeException e) {
      // Expected.
    }
  }

  public void testFallbackToCountry() {
    // Admin Area is missing.
    AddressData address = new AddressData.Builder().setCountry("US").setLocality("Mt View").build();

    LookupKey key = new LookupKey.Builder(KeyType.DATA).setAddressData(address).build();

    assertEquals("locality should be omitted since admin area is not specified", US_KEY,
        key.toString());

    // Tries key string with the same problem (missing Admin Area).
    key = new LookupKey.Builder("data/US//Mt View").build();

    assertEquals("locality should be omitted since admin area is not specified", US_KEY,
        key.toString());
  }

  public void testNonUsAddress() {
    AddressData address = new AddressData.Builder()
        .setCountry("TW")
        .setAdminArea("\u53F0\u5317\u5E02")  // Taipei City
        .setLocality("\u5927\u5B89\u5340")  // Da-an District
        .build();

    LookupKey key = new LookupKey.Builder(KeyType.DATA).setAddressData(address).build();
    assertEquals(TW_KEY, key.toString());

    key = new LookupKey.Builder(KeyType.EXAMPLES).setAddressData(address).build();
    assertEquals(TW_EXAMPLE_LOCAL_KEY, key.toString());

    address = new AddressData.Builder(address).setLanguageCode("zh-latn").build();
    key = new LookupKey.Builder(KeyType.EXAMPLES).setAddressData(address).build();
    assertEquals(TW_EXAMPLE_LATIN_KEY, key.toString());
  }

  public void testGetKeyForUpperLevelFieldWithDataKey() {
    AddressData address = new AddressData.Builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mt View")
        .build();

    LookupKey key = new LookupKey.Builder(KeyType.DATA).setAddressData(address).build();
    LookupKey newKey = key.getKeyForUpperLevelField(AddressField.COUNTRY);
    assertNotNull("failed to get key for " + AddressField.COUNTRY, newKey);
    assertEquals("data/US", newKey.toString());

    newKey = key.getKeyForUpperLevelField(AddressField.ADMIN_AREA);
    assertNotNull("failed to get key for " + AddressField.ADMIN_AREA, newKey);
    assertEquals("data/US/CA", newKey.toString());
    assertEquals("original key should not be changed", "data/US/CA/Mt View", key.toString());

    newKey = key.getKeyForUpperLevelField(AddressField.LOCALITY);
    assertNotNull("failed to get key for " + AddressField.LOCALITY, newKey);
    assertEquals("data/US/CA/Mt View", newKey.toString());

    newKey = key.getKeyForUpperLevelField(AddressField.DEPENDENT_LOCALITY);
    assertNull("should return null for field not contained in current key", newKey);

    newKey = key.getKeyForUpperLevelField(AddressField.RECIPIENT);
    assertNull("should return null since field '" + AddressField.RECIPIENT
        + "' is not in address hierarchy", newKey);
  }

  public void testGetKeyForUpperLevelFieldWithExampleKey() {
    LookupKey key = new LookupKey.Builder("examples/US/latin/_default").build();

    try {
      key.getKeyForUpperLevelField(AddressField.COUNTRY);
      fail("should fail if you try to get parent key for an example key.");
    } catch (RuntimeException e) {
      // Expected.
    }
  }

  public void testGetParentKeyStartingFromAddressWithLanguageSpecified() {
    AddressData address = new AddressData.Builder().setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mt View")
        .setDependentLocality("El Camino")
        .setLanguageCode("en")
        .build();

    LookupKey key = new LookupKey.Builder(KeyType.DATA).setAddressData(address).build();
    assertEquals("data/US/CA/Mt View/El Camino--en", key.toString());

    key = key.getParentKey();
    assertEquals("data/US/CA/Mt View--en", key.toString());

    key = key.getParentKey();
    assertEquals("data/US/CA--en", key.toString());

    key = key.getParentKey();
    assertEquals("data/US--en", key.toString());

    key = key.getParentKey();
    assertEquals("data", key.toString());

    key = key.getParentKey();
    assertNull("root key's parent should be null", key);
  }

  public void testGetParentKeyStartingFromAddress() {
    AddressData address = new AddressData.Builder()
        .setCountry("US")
        .setAdminArea("CA")
        .setLocality("Mt View")
        .setDependentLocality("El Camino")
        .build();

    LookupKey key = new LookupKey.Builder(KeyType.DATA).setAddressData(address).build();
    assertEquals("data/US/CA/Mt View/El Camino", key.toString());

    key = key.getParentKey();
    assertEquals("data/US/CA/Mt View", key.toString());

    key = key.getParentKey();
    assertEquals("data/US/CA", key.toString());

    key = key.getParentKey();
    assertEquals("data/US", key.toString());

    key = key.getParentKey();
    assertEquals("data", key.toString());

    key = key.getParentKey();
    assertNull("root key's parent should be null", key);
  }

  public void testInvalidKeyTypeWillFail() {
    try {
      new LookupKey.Builder(RANDOM_KEY).build();
      fail("Should fail if key string does not start with a valid key type");
    } catch (RuntimeException e) {
      // Expected.
    }
  }

  /**
   * Ensures that even when the input key string is random, we still create a key. (We do not verify
   * if the key maps to an real world entity like a city or country).
   */
  public void testWeDoNotVerifyKeyName() {
    LookupKey key = new LookupKey.Builder(RANDOM_COUNTRY_KEY).build();
    assertEquals(RANDOM_COUNTRY_KEY, key.toString());
  }

  public void testHash() {
    String keys[] = {ROOT_KEY, ROOT_EXAMPLE_KEY, US_KEY, CALIFORNIA_KEY};
    Map<LookupKey, String> map = new HashMap<LookupKey, String>();

    for (String key : keys) {
      map.put(new LookupKey.Builder(key).build(), key);
    }

    for (String key : keys) {
      assertTrue(map.containsKey(new LookupKey.Builder(key).build()));
      assertEquals(key, map.get(new LookupKey.Builder(key).build()));
    }
    assertFalse(map.containsKey(new LookupKey.Builder(RANDOM_COUNTRY_KEY).build()));
  }

  public void testGetValueForUpperLevelField() {
    LookupKey key = new LookupKey.Builder("data/US/CA").build();
    assertEquals("US", key.getValueForUpperLevelField(AddressField.COUNTRY));
  }

  public void testGetValueForUpperLevelFieldInvalid() {
    LookupKey key = new LookupKey.Builder("data").build();
    assertEquals("", key.getValueForUpperLevelField(AddressField.COUNTRY));
    LookupKey key2 = new LookupKey.Builder("data/").build();
    assertEquals("", key2.getValueForUpperLevelField(AddressField.COUNTRY));
  }
}
