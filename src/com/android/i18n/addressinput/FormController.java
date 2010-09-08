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
import com.android.i18n.addressinput.LookupKey.ScriptType;

import java.util.ArrayList;
import java.util.List;

/**
 * Controller for an Address Display and is responsible for:
 *
 * <ul>
 * <li>Providing a way to iterate over {@link AddressField}s in a country
 *     dependent way.
 * <li>Fetches new address data from the server as needed (based on hierarchy
 *     rules of international addresses).
 * <li>Provides {@link FormField} for an {@link AddressField}. A
 *     {@link FormField} provides Country specific data for that field. For
 *     example, returning the correct label for Administrative Area.
 * </ul>
 *
 * <p>
 * In order for FormController to work properly, it requires two things:
 * <ul>
 * <li>An implementation of {@link AddressDisplayHandler}, which can be set
 *     using {@link #initDisplayHandler(AddressDisplayHandler)}.
 * <li>Registering UI widgets which can change using
 *     {@link #registerField(AddressField, HasChangeHandlers)}. The registration
 *     should happen in constructor of the display. This registration is
 *     necessary so the controller can monitor changes and react to them
 *     appropriately. For example, a change in Country can cause additional
 *     data to be fetched and may cause a change in layout.
 * </ul>
 */
public class FormController {
  // For address hierarchy in lookup key.
  private static final String SLASH_DELIM = "/";
  // For joined values.
  private static final String TILDA_DELIM = "~";
  // For language code info in lookup key (E.g., data/CA--fr).
  private static final String DASH_DELIM = "--";

  private static final LookupKey ROOT_KEY = FormController.getDataKeyForRoot();
  private static final String DEFAULT_REGION_CODE = "ZZ";
  private final AddressVerificationNodeData DEFAULT_COUNTRY_DATA;

  private ClientData integratedData;

  // Constructor that populates this with data.
  public FormController(ClientData integratedData) {
    Util.checkNotNull(integratedData, "null data not allowed");

    AddressData address = new AddressData.Builder().setCountry(DEFAULT_REGION_CODE).build();
    LookupKey defaultCountryKey = getDataKeyFor(address);

    DEFAULT_COUNTRY_DATA = integratedData.getDefaultData(defaultCountryKey.toString());
    Util.checkNotNull(DEFAULT_COUNTRY_DATA,
                      "require data for default country key: " + defaultCountryKey);
    this.integratedData = integratedData;
  }

  private ScriptType getScriptType() {
    // TODO: Get the language code from somewhere. Ideally, we need a method to interpret a sensible
    // language code based on things like input method, locale.
    String languageCode = "en";
    if (languageCode != null && Util.isExplicitLatinScript(languageCode)) {
      return ScriptType.LATIN;
    }
    return ScriptType.LOCAL;
  }

  private static LookupKey getDataKeyForRoot() {
    AddressData address = new AddressData.Builder().build();
    return new LookupKey.Builder(KeyType.DATA).setAddressData(address).build();
  }

  private LookupKey getDataKeyFor(AddressData address) {
    return new LookupKey.Builder(KeyType.DATA).setAddressData(address).build();
  }

  /**
   * Gets a list of {@link RegionData} for sub-regions for a given key. For
   * example, sub regions for "data/US" are AL/Alabama, AK/Alaska, etc.
   *
   * <p>
   * TODO: It seems more straight forward to return a list of pairs
   * instead of RegionData. Actually, we can remove RegionData since it does
   * not contain anything more than key/value pairs now.
   *
   * @return A list of sub-regions, each sub-region represented by a
   *         {@link RegionData}.
   */
  List<RegionData> getRegionData(LookupKey key) {
    if (key.getKeyType() == KeyType.EXAMPLES) {
      throw new RuntimeException("example key not allowed for getting region data");
    }
    Util.checkNotNull(key, "null regionKey not allowed");
    LookupKey normalizedKey = normalizeLookupKey(key);
    List<RegionData> results = new ArrayList<RegionData>();

    // Root key.
    if (normalizedKey.equals(ROOT_KEY)) {
      AddressVerificationNodeData data =
          integratedData.getDefaultData(normalizedKey.toString());
      String[] countries = splitData(data.get(AddressDataKey.COUNTRIES));
      for (int i = 0; i < countries.length; i++) {
        RegionData rd = new RegionData.Builder()
            .setKey(countries[i])
            .setName(countries[i])
            .build();
        results.add(rd);
      }
      return results;
    }

    AddressVerificationNodeData data =
        integratedData.get(normalizedKey.toString());
    if (data != null) {
      String[] keys = splitData(data.get(AddressDataKey.SUB_KEYS));
      String[] names = (getScriptType() == ScriptType.LOCAL)
          ? splitData(data.get(AddressDataKey.SUB_NAMES))
          : splitData(data.get(AddressDataKey.SUB_LNAMES));

      for (int i = 0; i < keys.length; i++) {
        RegionData rd =
            new RegionData.Builder()
            .setKey(keys[i])
            .setName((i < names.length) ? names[i] : keys[i])
            .build();
        results.add(rd);
      }
    }
    return results;
  }

  /**
   * Split a '~' delimited string into an array of strings. This method is null
   * tolerant and considers an empty string to contain no elements.
   *
   * @param raw The data to split
   * @return an array of strings
   */
  private String[] splitData(String raw) {
    if (raw == null || raw.isEmpty()) {
      return new String[] {};
    }
    return raw.split(TILDA_DELIM);
  }

  private String getSubKey(LookupKey parentKey, String name) {
    for (RegionData subRegion : getRegionData(parentKey)) {
      if (subRegion.isValidName(name)) {
        return subRegion.getKey();
      }
    }
    return null;
  }

  /**
   * Normalizes {@code key} by replacing field values with sub-keys. For
   * example, California is replaced with CA. The normalization goes from top
   * (country) to bottom (dependent locality) and if any field value is empty,
   * unknown, or invalid, it will stop and return whatever it gets. For example,
   * a key "data/US/California/foobar/kar" will be normalized into
   * "data/US/CA/foobar/kar" since "foobar" is unknown. This method supports
   * only key of {@link KeyType#DATA} type.
   *
   * @return normalized {@link LookupKey}.
   */
  private LookupKey normalizeLookupKey(LookupKey key) {
    Util.checkNotNull(key);
    if (key.getKeyType() != KeyType.DATA) {
      throw new RuntimeException("Only DATA keyType is supported");
    }

    String subStr[] = key.toString().split(SLASH_DELIM);

    // Root key does not need to be normalized.
    if (subStr.length < 2) {
      return key;
    }

    StringBuilder sb = new StringBuilder(subStr[0]);
    for (int i = 1; i < subStr.length; ++i) {
      // Strips the language code if contained.
      String languageCode = null;
      if (i == 1 && subStr[i].contains(DASH_DELIM)) {
        String[] s = subStr[i].split(DASH_DELIM);
        subStr[i] = s[0];
        languageCode = s[1];
      }

      String normalizedSubKey = getSubKey(new LookupKey.Builder(sb.toString()).build(), subStr[i]);

      // Can't find normalized sub-key; assembles the lookup key with the
      // remaining sub-keys and returns it.
      if (normalizedSubKey == null) {
        for (; i < subStr.length; ++i) {
          sb.append(SLASH_DELIM).append(subStr[i]);
        }
        break;
      }
      sb.append(SLASH_DELIM).append(normalizedSubKey);
      if (languageCode != null) {
        sb.append(DASH_DELIM).append(languageCode);
      }
    }
    return new LookupKey.Builder(sb.toString()).build();
  }
}
