package com.google.i18n.addressinput.testing;

import com.google.i18n.addressinput.common.AsyncRequestApi;
import com.google.i18n.addressinput.common.JsoMap;

import org.json.JSONException;

import java.util.HashMap;
import java.util.Map;

/**
 * Fake implementation of AsyncRequestApi which loads data synchronously and immediately.
 * Can be used manually with custom test data or with a snapshot of real data found in
 * {@link AddressDataMapLoader#TEST_COUNTRY_DATA}.
 */
public class InMemoryAsyncRequest implements AsyncRequestApi {
  private final Map<String, JsoMap> responseMap = new HashMap<String, JsoMap>();

  public InMemoryAsyncRequest(String urlPrefix, Map<String, String> keyToJsonMap) {
    try {
      for (Map.Entry<String, String> e : keyToJsonMap.entrySet()) {
        responseMap.put(urlPrefix + "/" + e.getKey(), JsoMap.buildJsoMap(e.getValue()));
      }
    } catch (JSONException e) {
      throw new AssertionError("Invalid test JSON data: " + keyToJsonMap, e);
    }
  }

  @Override
  public void requestObject(String url, AsyncCallback callback, int timeoutMillis) {
    if (responseMap.containsKey(url)) {
      callback.onSuccess(responseMap.get(url));
    } else {
      callback.onFailure();
    }
  }
}
