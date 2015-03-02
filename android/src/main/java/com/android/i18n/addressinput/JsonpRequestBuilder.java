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

import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

/**
 * Android implementation of those parts of the com.google.gwt.jsonp.client.JsonpRequestBuilder
 * class that the CacheData class uses.
 */
class JsonpRequestBuilder {

  /**
   * Re-implementation of the com.google.gwt.user.client.rpc.AsyncCallback interface.
   */
  interface AsyncCallback<T> {

    public void onFailure(Throwable caught);

    public void onSuccess(T result);
  }

  /**
   * @param timeout The expected timeout (ms) for this request.
   */
  void setTimeout(int timeout) {
    HttpParams params = AsyncHttp.CLIENT.getParams();
    HttpConnectionParams.setConnectionTimeout(params, timeout);
    HttpConnectionParams.setSoTimeout(params, timeout);
  }

  /**
   * Sends a JSONP request and expects a JsoMap object as a result.
   */
  void requestObject(String url, AsyncCallback<JsoMap> callback) {
    HttpUriRequest request = new HttpGet(encodeUrl(url));
    (new AsyncHttp(request, callback)).start();
  }

  /**
   * Simple implementation of asynchronous HTTP GET.
   */
  private static class AsyncHttp extends Thread {

    private static final HttpClient CLIENT = new DefaultHttpClient();

    private HttpUriRequest request;

    private AsyncCallback<JsoMap> callback;

    protected AsyncHttp(HttpUriRequest request, AsyncCallback<JsoMap> callback) {
      this.request = request;
      this.callback = callback;
    }

    @Override
    public void run() {
      try {
        final String response;
        synchronized (CLIENT) {
          response = CLIENT.execute(request, new BasicResponseHandler());
        }
        callback.onSuccess(JsoMap.buildJsoMap(response));
      } catch (Exception e) {
        callback.onFailure(e);
      }
    }
  }

  /**
   * A quick hack to transform a string into an RFC 3986 compliant URL.
   *
   * TODO: Refactor the code to stop passing URLs around as strings, to eliminate the need for
   * this hack.
   */
  private static String encodeUrl(String url) {
    int length = url.length();
    StringBuilder tmp = new StringBuilder(length);

    try {
      for (int i = 0; i < length; i++) {
        int j = i;
        char c = '\0';
        for (; j < length; j++) {
          c = url.charAt(j);
          if (c == ':' || c == '/') {
            break;
          }
        }
        if (j == length) {
          tmp.append(URLEncoder.encode(url.substring(i), "UTF-8"));
          break;
        } else if (j > i) {
          tmp.append(URLEncoder.encode(url.substring(i, j), "UTF-8"));
          tmp.append(c);
          i = j;
        } else {
          tmp.append(c);
        }
      }
    } catch (UnsupportedEncodingException e) {
      throw new RuntimeException(e);  // Impossible.
    }

    return tmp.toString();
  }
}
