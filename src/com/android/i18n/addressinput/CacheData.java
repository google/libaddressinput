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

import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONObject;

import android.util.Log;

import java.util.EventListener;
import java.util.HashMap;
import java.util.HashSet;

/**
 * Cache for dynamic address data.
 *
 */
public final class CacheData {
  private static final String TAG = "CacheData";  // Used to identify the source of a log message.

  /**
   * Time out value for the server to respond in millisecond.
   */
  private final int TIMEOUT = 5000;

  /**
   * URL to get public address data.
   */
  private final String PUBLIC_ADDRESS_DATA_SERVER =
      "http://i18napis.appspot.com/address";

  /**
   * Url to get address data. You can also reset it by calling
   * {@link #setUrl(String)}.
   *
   */
  private String serviceUrl = PUBLIC_ADDRESS_DATA_SERVER;

  /**
   * Storage for all dynamically retrieved data.
   */
  private final JsoMap theCache = JsoMap.createEmptyJsoMap();

  /**
   * All requests that have been sent.
   */
  private final HashSet<String> requestedKeys = new HashSet<String>();

  /**
   * All invalid requested keys. For example, if we request a random string
   * "asdfsdf9o", and the server responds by saying this key is invalid, it will
   * be stored here.
   */
  private final HashSet<String> badKeys = new HashSet<String>();

  /**
   * Temporary store for {@code MyCacheListener}s. When a key is requested and
   * still waiting for server's response, the listeners for the same key will be
   * temporary stored here. When the server responded, these listeners will
   * be triggered and then removed.
   */
  private final HashMap<LookupKey, HashSet<MyCacheListener>> temporaryListenerStore =
    new HashMap<LookupKey, HashSet<MyCacheListener>>();

  /**
   * Interface for all listeners to {@link CacheData} change. This is only
   * used when multiple requests of the same key is dispatched and server has
   * not responded yet.
   *
   */
  private static interface MyCacheListener extends EventListener {
    /**
     * The function that will be called when valid data is about to be put
     * in the cache.
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
     * @param key The key for requested data.
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
     * Saves valid responded data to the cache once data arrives, or if the key
     * is invalid, saves it in the invalid cache. If there is
     * pre-existing data for the key, it will merge the new data will the
     * old one. It also triggers {@link DataLoadListener#dataLoadingEnd()}
     * method before it returns (even when the key is invalid, or input jso
     * is null).
     *
     * @param map The received JSON data as a map.
     */
    private void handleJson(JsoMap map) {
      // Can this ever happen?
      if (map == null) {
        Log.w(TAG, "server returns null for key:" + key);
        badKeys.add(key);
        notifyListenersAfterJobDone(key);
        triggerDataLoadingEndIfNotNull(listener);
        return;
      }

      JSONObject json = (JSONObject)map;
      String idKey = AddressDataKey.ID.name().toLowerCase();
      if (!json.has(idKey)) {
        Log.w(TAG, "invalid or empty data returned for key: " + key);
        badKeys.add(key);
        notifyListenersAfterJobDone(key);
        triggerDataLoadingEndIfNotNull(listener);
        return;
      }

      if (existingJso != null) {
        map.mergeData((JsoMap) existingJso);
      }

      Log.w(TAG, "put the following key/value pair into cache. key:" + key
          + ", value:" + map.string());
      theCache.putObj(key, map);
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
    serviceUrl = url;
  }

  /**
   * Gets address data server URL.
   */
  public String getUrl() {
    return serviceUrl;
  }

  /**
   * Checks if key and its value is cached (Note that only valid ones
   * are cached).
   */
  public boolean containsKey(String key) {
    return theCache.containsKey(key);
  }

  private void triggerDataLoadingEndIfNotNull(DataLoadListener listener) {
    if (listener != null) {
      listener.dataLoadingEnd();
    }
  }

  /**
   * Fetches data from server, or returns if the data is already cached. If the
   * fetched data is valid, it will be added to the cache. This method also
   * triggers {@link DataLoadListener#dataLoadingEnd()} method before it
   * returns.
   *
   * @param existingJso Pre-existing data for this key or null if none.
   * @param listener An optional listener to call when done.
   */
  public  // TODO: Remove this "public" when it's no longer used for testing.
  void fetchDynamicData(final LookupKey key,
      JSONObject existingJso,
      final DataLoadListener listener) {
    checkNotNull(key, "null key not allowed.");

    if (listener != null) {
      listener.dataLoadingBegin();
    }

    // Key is valid and cached.
    if (theCache.containsKey(key.toString())) {
      Log.w(TAG, "returning data for key " + key + " from the cache");
      triggerDataLoadingEndIfNotNull(listener);
      return;
    }

    // Key is invalid and cached.
    if (badKeys.contains(key.toString())) {
      triggerDataLoadingEndIfNotNull(listener);
      return;
    }

    // Already requested the key, and is still waiting for server's response.
    if (!requestedKeys.add(key.toString())) {
      Log.w(TAG, "data for key " + key + " requested but not cached yet");
      addListenerToTempStore(key, new MyCacheListener() {
        public void onAdd(String myKey) {
          triggerDataLoadingEndIfNotNull(listener);
        }
      });
      return;
    }

    // Key is not cached yet, now sending the request to the server.
    JsonpRequestBuilder jsonp = new JsonpRequestBuilder();
    jsonp.setTimeout(TIMEOUT);
    final JsonHandler handler = new JsonHandler(key.toString(),
        existingJso, listener);
    jsonp.requestObject(serviceUrl + "/" + key.toString(),
        new AsyncCallback<JsoMap>() {
          public void onFailure(Throwable caught) {
            Log.w(TAG, "Request for key " + key + " failed");
            requestedKeys.remove(key.toString());
            notifyListenersAfterJobDone(key.toString());
            triggerDataLoadingEndIfNotNull(listener);
          }

          public void onSuccess(JsoMap result) {
            handler.handleJson(result);
          }
        });
  }

  /**
   * Retrieves string data identified by key.
   *
   * @param key Non-null key. E.g., "data/US/CA".
   * @return String value for specified key.
   */
  public String get(String key) {
    checkNotNull(key, "null key not allowed");
    return theCache.get(key);
  }

  /**
   * Retrieves JsoMap data identified by key.
   *
   * @param key Non-null key. E.g., "data/US/CA".
   * @return String value for specified key.
   */
  public JsoMap getObj(String key) {
    checkNotNull(key, "null key not allowed");
    return theCache.getObj(key);
  }

  private void notifyListenersAfterJobDone(String key) {
    LookupKey lookupKey = new LookupKey.Builder(key).build();
    HashSet<MyCacheListener> listeners = temporaryListenerStore.get(lookupKey);
    if (listeners != null) {
      for (MyCacheListener listener : listeners) {
        listener.onAdd(key.toString());
      }
      listeners.clear();
    }
  }

  private void addListenerToTempStore(LookupKey key, MyCacheListener listener) {
    checkNotNull(key);
    checkNotNull(listener);
    HashSet<MyCacheListener> listeners = temporaryListenerStore.get(key);
    if (listeners == null) {
      listeners = new HashSet<MyCacheListener>();      
      temporaryListenerStore.put(key, listeners);
    }
    listeners.add(listener);
  }

  //
  // Temporary implementations of things that the GWT implementation depends on.
  //
  // TODO: Write real implementations and remove these.
  //

  private interface AsyncCallback<T> {
    public void onFailure(Throwable caught);
    public void onSuccess(T result);
  }

  private static class JsonpRequestBuilder {
    // This method doesn't do anything.
    // TODO: Rewrite to actually set the timeout.
    public void setTimeout(int timeout) {
    }

    public void requestObject(String url, AsyncCallback<JsoMap> callback) {
      HttpUriRequest request = new HttpGet(url);
      (new AsyncHttp(request, callback)).start();
    }

    // Simple implementation of asynchronous HTTP GET.
    // TODO: Replace with something more sophisticated.
    private static class AsyncHttp extends Thread {
      private static final HttpClient client = new DefaultHttpClient();

      private HttpUriRequest request;
      private AsyncCallback<JsoMap> callback;

      protected AsyncHttp(HttpUriRequest request, AsyncCallback<JsoMap> callback) {
        this.request = request;
        this.callback = callback;
      }

      public void run() {
        try {
          final String response;
          synchronized (client) {
            response = client.execute(request, new BasicResponseHandler());
          }
          callback.onSuccess(JsoMap.buildJsoMap(response));
        } catch (Exception e) {
          callback.onFailure(e);
        }
      }
    }
  }
}
