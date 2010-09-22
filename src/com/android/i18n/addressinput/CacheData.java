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

import static com.android.i18n.addressinput.Util.checkNotNull;

import com.android.i18n.addressinput.JsonpRequestBuilder.AsyncCallback;

import android.util.Log;

import org.json.JSONObject;

import java.util.EventListener;
import java.util.HashMap;
import java.util.HashSet;

/**
 * Cache for dynamic address data.
 */
public final class CacheData {

    /**
     * Used to identify the source of a log message.
     */
    private static final String sTag = "CacheData";

    /**
     * Time out value for the server to respond in millisecond.
     */
    private final int mTimeout = 5000;

    /**
     * CacheData singleton.
     */
    private static final CacheData sInstance = new CacheData();

    /**
     * URL to get public address data.
     */
    private static final String sPublicAddressDataServer =
            "http://i18napis.appspot.com/address";

    /**
     * URL to get address data. You can also reset it by calling {@link #setUrl(String)}.
     */
    private String mServiceUrl = sPublicAddressDataServer;

    /**
     * Storage for all dynamically retrieved data.
     */
    private final JsoMap mCache = JsoMap.createEmptyJsoMap();

    /**
     * All requests that have been sent.
     */
    private final HashSet<String> mRequestedKeys = new HashSet<String>();

    /**
     * All invalid requested keys. For example, if we request a random string "asdfsdf9o", and the
     * server responds by saying this key is invalid, it will be stored here.
     */
    private final HashSet<String> mBadKeys = new HashSet<String>();

    /**
     * Temporary store for {@code CacheListener}s. When a key is requested and still waiting for
     * server's response, the listeners for the same key will be temporary stored here. When the
     * server responded, these listeners will be triggered and then removed.
     */
    private final HashMap<LookupKey, HashSet<CacheListener>> mTemporaryListenerStore =
            new HashMap<LookupKey, HashSet<CacheListener>>();

    /**
     * Private constructor - singleton class.
     */
    private CacheData() {
    }

    /**
     * Interface for all listeners to {@link CacheData} change. This is only used when multiple
     * requests of the same key is dispatched and server has not responded yet.
     */
    private static interface CacheListener extends EventListener {

        /**
         * The function that will be called when valid data is about to be put in the cache.
         *
         * @param key the key for newly arrived data.
         */
        void onAdd(String key);
    }

    /**
     * Class to handle JSON response.
     */
    private class JsonHandler {

        /**
         * Key for the requested data.
         */
        private final String key;

        /**
         * Pre-existing data for the requested key. Null is allowed.
         */
        private final JSONObject existingJso;

        private final DataLoadListener listener;

        /**
         * Constructs a JsonHandler instance.
         *
         * @param key    The key for requested data.
         * @param oldJso Pre-existing data for this key or null.
         */
        private JsonHandler(String key, JSONObject oldJso,
                DataLoadListener listener) {
            checkNotNull(key);
            this.key = key;
            this.existingJso = oldJso;
            this.listener = listener;
        }

        /**
         * Saves valid responded data to the cache once data arrives, or if the key is invalid,
         * saves it in the invalid cache. If there is pre-existing data for the key, it will merge
         * the new data will the old one. It also triggers {@link DataLoadListener#dataLoadingEnd()}
         * method before it returns (even when the key is invalid, or input jso is null).
         *
         * @param map The received JSON data as a map.
         */
        private void handleJson(JsoMap map) {
            // Can this ever happen?
            if (map == null) {
                Log.w(sTag, "server returns null for key:" + key);
                mBadKeys.add(key);
                notifyListenersAfterJobDone(key);
                triggerDataLoadingEndIfNotNull(listener);
                return;
            }

            JSONObject json = map;
            String idKey = AddressDataKey.ID.name().toLowerCase();
            if (!json.has(idKey)) {
                Log.w(sTag, "invalid or empty data returned for key: " + key);
                mBadKeys.add(key);
                notifyListenersAfterJobDone(key);
                triggerDataLoadingEndIfNotNull(listener);
                return;
            }

            if (existingJso != null) {
                map.mergeData((JsoMap) existingJso);
            }

            Log.w(sTag, "put the following key/value pair into cache. key:" + key
                    + ", value:" + map.string());
            mCache.putObj(key, map);
            notifyListenersAfterJobDone(key);
            triggerDataLoadingEndIfNotNull(listener);
        }
    }

    /**
     * Sets address data server URL. Input URL cannot be null.
     *
     * @param url The service URL.
     */
    public void setUrl(String url) {
        checkNotNull(url, "Cannot set URL of address data server to null.");
        mServiceUrl = url;
    }

    /**
     * Gets address data server URL.
     */
    public String getUrl() {
        return mServiceUrl;
    }

    /**
     * Checks if key and its value is cached (Note that only valid ones are cached).
     */
    public boolean containsKey(String key) {
        return mCache.containsKey(key);
    }

    private void triggerDataLoadingEndIfNotNull(DataLoadListener listener) {
        if (listener != null) {
            listener.dataLoadingEnd();
        }
    }

    /**
     * Fetches data from server, or returns if the data is already cached. If the fetched data is
     * valid, it will be added to the cache. This method also triggers {@link
     * DataLoadListener#dataLoadingEnd()} method before it returns.
     *
     * @param existingJso Pre-existing data for this key or null if none.
     * @param listener    An optional listener to call when done.
     */
    void fetchDynamicData(final LookupKey key,
            JSONObject existingJso,
            final DataLoadListener listener) {
        checkNotNull(key, "null key not allowed.");

        if (listener != null) {
            listener.dataLoadingBegin();
        }

        // Key is valid and cached.
        if (mCache.containsKey(key.toString())) {
            Log.w(sTag, "returning data for key " + key + " from the cache");
            triggerDataLoadingEndIfNotNull(listener);
            return;
        }

        // Key is invalid and cached.
        if (mBadKeys.contains(key.toString())) {
            triggerDataLoadingEndIfNotNull(listener);
            return;
        }

        // Already requested the key, and is still waiting for server's response.
        if (!mRequestedKeys.add(key.toString())) {
            Log.w(sTag, "data for key " + key + " requested but not cached yet");
            addListenerToTempStore(key, new CacheListener() {
                public void onAdd(String myKey) {
                    triggerDataLoadingEndIfNotNull(listener);
                }
            });
            return;
        }

        // Key is not cached yet, now sending the request to the server.
        JsonpRequestBuilder jsonp = new JsonpRequestBuilder();
        jsonp.setTimeout(mTimeout);
        final JsonHandler handler = new JsonHandler(key.toString(),
                existingJso, listener);
        jsonp.requestObject(mServiceUrl + "/" + key.toString(),
                new AsyncCallback<JsoMap>() {
                    public void onFailure(Throwable caught) {
                        Log.w(sTag, "Request for key " + key + " failed");
                        mRequestedKeys.remove(key.toString());
                        notifyListenersAfterJobDone(key.toString());
                        triggerDataLoadingEndIfNotNull(listener);
                    }

                    public void onSuccess(JsoMap result) {
                        handler.handleJson(result);
                    }
                });
    }

    /**
     * Gets the instance of CacheData.
     */
    public static CacheData getInstance() {
        return sInstance;
    }

    /**
     * Retrieves string data identified by key.
     *
     * @param key Non-null key. E.g., "data/US/CA".
     * @return String value for specified key.
     */
    public String get(String key) {
        checkNotNull(key, "null key not allowed");
        return mCache.get(key);
    }

    /**
     * Retrieves JsoMap data identified by key.
     *
     * @param key Non-null key. E.g., "data/US/CA".
     * @return String value for specified key.
     */
    public JsoMap getObj(String key) {
        checkNotNull(key, "null key not allowed");
        return mCache.getObj(key);
    }

    private void notifyListenersAfterJobDone(String key) {
        LookupKey lookupKey = new LookupKey.Builder(key).build();
        HashSet<CacheListener> listeners = mTemporaryListenerStore.get(lookupKey);
        if (listeners != null) {
            for (CacheListener listener : listeners) {
                listener.onAdd(key.toString());
            }
            listeners.clear();
        }
    }

    private void addListenerToTempStore(LookupKey key, CacheListener listener) {
        checkNotNull(key);
        checkNotNull(listener);
        HashSet<CacheListener> listeners = mTemporaryListenerStore.get(key);
        if (listeners == null) {
            listeners = new HashSet<CacheListener>();
            mTemporaryListenerStore.put(key, listeners);
        }
        listeners.add(listener);
    }
}
