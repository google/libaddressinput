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

import org.json.JSONArray;
import org.json.JSONException;

import java.util.EnumMap;
import java.util.HashMap;
import java.util.Map;

/**
 * Access point for the cached address verification data. The data contained here will mainly be
 * used to build {@link FieldVerifier}'s. This class is implemented as a singleton.
 */
public class ClientData {

  /* Data to bootstrap the process. The data are all regional (country level)
   * data. Keys are like "data/US/CA"
   */
  private final Map<String, JsoMap> bootstrapMap = new HashMap<String, JsoMap>();

  private CacheData cacheData;

  public ClientData(RegionDataConstants regionDataConstants, CacheData cacheData) {
    this.cacheData = cacheData;
    buildRegionalData();
  }

  public AddressVerificationNodeData get(String key) {
    JsoMap jso = cacheData.getObj(key);
    if (jso != null && isValidDataKey(key)) {
      return createNodeData(jso);
    } else {
      fetchDataIfNotAvailable(key);
    }
    return null;
  }

  public AddressVerificationNodeData getDefaultData(String key) {
    // root data
    if (key.split("/").length == 1) {
      JsoMap jso = bootstrapMap.get(key);
      if (jso == null || !isValidDataKey(key)) {
        throw new RuntimeException("key " + key + " does not have bootstrap data");
      }
      return createNodeData(jso);
    }

    key = getCountryKey(key);
    JsoMap jso = bootstrapMap.get(key);
    if (jso == null || !isValidDataKey(key)) {
      throw new RuntimeException("key " + key + " does not have bootstrap data");
    }
    return createNodeData(jso);
  }

  private String getCountryKey(String hierarchyKey) {
    if (hierarchyKey.split("/").length <= 1) {
      throw new RuntimeException("Cannot get country key with key '" + hierarchyKey + "'");
    }
    if (isCountryKey(hierarchyKey)) {
      return hierarchyKey;
    }

    String[] parts = hierarchyKey.split("/");

    return new StringBuilder().append(parts[0])
        .append("/")
        .append(parts[1])
        .toString();
  }

  private boolean isCountryKey(String hierarchyKey) {
    Util.checkNotNull(hierarchyKey, "Cannot use null as a key");
    return hierarchyKey.split("/").length == 2;
  }


  /**
   * Returns the contents of the JSON-format string as a map.
   */
  protected AddressVerificationNodeData createNodeData(JsoMap jso) {
    Map<AddressDataKey, String> map =
        new EnumMap<AddressDataKey, String>(AddressDataKey.class);

    JSONArray arr = jso.getKeys();
    for (int i = 0; i < arr.length(); i++) {
      try {
        AddressDataKey key = AddressDataKey.get(arr.getString(i));

        /* This is a runtime data sanity check.  The data should be
         * checked when the data is built. There should be no key
         * that does not match an AddressDataKey.
         */
        Util.checkNotNull(key, "Unknown field for key '" + arr.getString(i) + "'");

        String value = jso.get(key.toString().toLowerCase());
        map.put(key, value);
      } catch (JSONException e) {
        // This should not happen - we should not be fetching a key from outside the bounds of the
        // array.
      }
    }

    return new AddressVerificationNodeData(map);
  }

  /**
   * We can be initialized with the full set of address information,
   * but validation only uses info prefixed with "data" (in
   * particular, no info prefixed with "examples").
   */
  private boolean isValidDataKey(String key) {
    return key.startsWith("data");
  }

  /**
   * Initializes regionalData structure based on property file.
   */
  private void buildRegionalData() {
    StringBuilder countries = new StringBuilder();

    for (String countryCode : RegionDataConstants.getCountryFormatMap().keySet()) {
      countries.append(countryCode + "~");
      String json = RegionDataConstants.getCountryFormatMap().get(countryCode);
      JsoMap jso = null;
      try {
        jso = JsoMap.buildJsoMap(json);
      } catch (JSONException e) {
        // Ignore.
      }

      AddressData data = new AddressData.Builder().setCountry(countryCode).build();
      LookupKey key = new LookupKey.Builder(KeyType.DATA).setAddressData(data).build();
      bootstrapMap.put(key.toString(), jso);
    }
    countries.setLength(countries.length() - 1);

    // TODO: this is messy. do we have better ways to do it?
    /* Creates verification data for key="data". This will be used for the
     * root FieldVerifier.
     */
    String str = "{\"id\":\"data\",\"" +
        AddressDataKey.COUNTRIES.toString().toLowerCase() +
        "\": \"" + countries.toString() + "\"}";
    JsoMap jsoData = null;
    try {
      jsoData = JsoMap.buildJsoMap(str);
    } catch (JSONException e) {
      // Ignore.
    }
    bootstrapMap.put("data", jsoData);
  }

  /**
   * Fetches data from remote server if it is not cached yet.
   *
   * @param key The key for data that being requested. Key can be either a
   * data key (starts with "data") or example key (starts with "examples")
   */
  private void fetchDataIfNotAvailable(String key) {
    JsoMap jso = cacheData.getObj(key);
    if (jso == null) {
      // If there is bootstrap data for the key, pass the data to fetchDynamicData
      JsoMap regionalData = bootstrapMap.get(key);
      cacheData.fetchDynamicData(new LookupKey.Builder(key).build(), regionalData, null);
    }
  }

  public void requestData(LookupKey key, DataLoadListener listener) {
    Util.checkNotNull(key, "Null lookup key not allowed");
    JsoMap regionalData = bootstrapMap.get(key.toString());
    cacheData.fetchDynamicData(key, regionalData, listener);
  }
}
