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

import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;

import java.util.EnumMap;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * Access point for the cached address verification data. The data contained here will mainly be
 * used to build {@link FieldVerifier}'s. This class is implemented as a singleton.
 */
public class ClientData implements DataSource {

    private static final String TAG = "ClientData";

    /**
     * Data to bootstrap the process. The data are all regional (country level)
     * data. Keys are like "data/US/CA"
     */
    private final Map<String, JsoMap> mBootstrapMap = new HashMap<String, JsoMap>();

    private CacheData mCacheData;

    public ClientData(CacheData cacheData) {
        this.mCacheData = cacheData;
        buildRegionalData();
    }

    @Override
    public AddressVerificationNodeData get(String key) {
        JsoMap jso = mCacheData.getObj(key);
        if (jso == null) {  // Not cached.
            fetchDataIfNotAvailable(key);
            jso = mCacheData.getObj(key);
        }
        if (jso != null && isValidDataKey(key)) {
            return createNodeData(jso);
        }
        return null;
    }

    @Override
    public AddressVerificationNodeData getDefaultData(String key) {
        // root data
        if (key.split("/").length == 1) {
            JsoMap jso = mBootstrapMap.get(key);
            if (jso == null || !isValidDataKey(key)) {
                throw new RuntimeException("key " + key + " does not have bootstrap data");
            }
            return createNodeData(jso);
        }

        key = getCountryKey(key);
        JsoMap jso = mBootstrapMap.get(key);
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

                if (key == null) {
                    // Not all keys are supported by Android, so we continue if we encounter one
                    // that is not used.
                    continue;
                }

                String value = jso.get(key.toString().toLowerCase());
                map.put(key, value);
            } catch (JSONException e) {
                // This should not happen - we should not be fetching a key from outside the bounds
                // of the array.
            }
        }

        return new AddressVerificationNodeData(map);
    }

    /**
     * We can be initialized with the full set of address information, but validation only uses info
     * prefixed with "data" (in particular, no info prefixed with "examples").
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
            mBootstrapMap.put(key.toString(), jso);
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
        mBootstrapMap.put("data", jsoData);
    }

    /**
     * Fetches data from remote server if it is not cached yet.
     *
     * @param key The key for data that being requested. Key can be either a data key (starts with
     *            "data") or example key (starts with "examples")
     */
    private void fetchDataIfNotAvailable(String key) {
        JsoMap jso = mCacheData.getObj(key);
        if (jso == null) {
            // If there is bootstrap data for the key, pass the data to fetchDynamicData
            JsoMap regionalData = mBootstrapMap.get(key);
            NotifyingListener listener = new NotifyingListener(this);
            // If the key was invalid, we don't want to attempt to fetch it.
            if (LookupKey.hasValidKeyPrefix(key)) {
                LookupKey lookupKey = new LookupKey.Builder(key).build();
                mCacheData.fetchDynamicData(lookupKey, regionalData, listener);
                try {
                    listener.waitLoadingEnd();
                    // Check to see if there is data for this key now.
                    if (mCacheData.getObj(key) == null && isCountryKey(key)) {
                        // If not, see if there is data in RegionDataConstants.
                        Log.i(TAG, "Server failure: looking up key in region data constants.");
                        mCacheData.getFromRegionDataConstants(lookupKey);
                    }
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public void requestData(LookupKey key, DataLoadListener listener) {
        Util.checkNotNull(key, "Null lookup key not allowed");
        JsoMap regionalData = mBootstrapMap.get(key.toString());
        mCacheData.fetchDynamicData(key, regionalData, listener);
    }

    /**
     * Fetches all data for the specified country from the remote server.
     */
    public void prefetchCountry(String country, DataLoadListener listener) {
        String key = "data/" + country;
        Set<RecursiveLoader> loaders = new HashSet<RecursiveLoader>();
        listener.dataLoadingBegin();
        mCacheData.fetchDynamicData(
                new LookupKey.Builder(key).build(),
                null,
                new RecursiveLoader(key, loaders, listener));
    }

    /**
     * A helper class to recursively load all sub keys using fetchDynamicData().
     */
    private class RecursiveLoader implements DataLoadListener {

        private final String key;

        private final Set<RecursiveLoader> loaders;

        private final DataLoadListener listener;

        public RecursiveLoader(String key, Set<RecursiveLoader> loaders,
                DataLoadListener listener) {
            this.key = key;
            this.loaders = loaders;
            this.listener = listener;

            synchronized (loaders) {
                loaders.add(this);
            }
        }

        @Override
        public void dataLoadingBegin() {
        }

        @Override
        public void dataLoadingEnd() {
            final String subKeys = AddressDataKey.SUB_KEYS.name().toLowerCase();
            final String subMores = AddressDataKey.SUB_MORES.name().toLowerCase();

            JsoMap map = mCacheData.getObj(key);

            if (map.containsKey(subMores)) {
                // This key could have sub keys.
                String[] mores = {};
                String[] keys = {};

                mores = map.get(subMores).split("~");

                if (map.containsKey(subKeys)) {
                    keys = map.get(subKeys).split("~");
                }

                if (mores.length != keys.length) {  // This should never happen.
                    throw new IndexOutOfBoundsException("mores.length != keys.length");
                }

                for (int i = 0; i < mores.length; i++) {
                    if (mores[i].equalsIgnoreCase("true")) {
                        // This key should have sub keys.
                        String subKey = key + "/" + keys[i];
                        mCacheData.fetchDynamicData(
                                new LookupKey.Builder(subKey).build(),
                                null,
                                new RecursiveLoader(subKey, loaders, listener));
                    }
                }
            }

            synchronized (loaders) {
                loaders.remove(this);
                if (loaders.isEmpty()) {
                    listener.dataLoadingEnd();
                }
            }
        }
    }
}
