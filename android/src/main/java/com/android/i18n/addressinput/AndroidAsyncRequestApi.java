/*
 * Copyright (C) 2015 Google Inc.
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

import com.google.i18n.addressinput.common.AsyncRequestApi;
import com.google.i18n.addressinput.common.JsoMap;

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
 * Android implementation of AsyncRequestApi.
 * <p>
 * Note that this class uses a thread-per-request approach to asynchronous connections. There are
 * likely to be better ways of doing this (and even if not, this implementation suffers from several
 * issues regarding interruption and cancellation). Ultimately this class should be revisited and
 * most likely rewritten.
 */
// TODO: Reimplement this class according to current bast-practice for asynchronous requests.
public class AndroidAsyncRequestApi implements AsyncRequestApi {
  /** Simple implementation of asynchronous HTTP GET. */
  private static class AsyncHttp extends Thread {
    private final HttpUriRequest request;
    private final AsyncCallback callback;

    protected AsyncHttp(HttpUriRequest request, AsyncCallback callback) {
      this.request = request;
      this.callback = callback;
    }

    @Override
    public void run() {
      try {
        final String response;
        // TODO: Figure out if this synchronization is even vaguely necessary.
        synchronized (CLIENT) {
          response = CLIENT.execute(request, new BasicResponseHandler());
        }
        callback.onSuccess(JsoMap.buildJsoMap(response));
      } catch (Exception e) {
        callback.onFailure();
      }
    }
  }

  private static final HttpClient CLIENT = new DefaultHttpClient();

  @Override public void requestObject(String url, AsyncCallback callback, int timeoutMillis) {
    HttpParams params = CLIENT.getParams();
    HttpConnectionParams.setConnectionTimeout(params, timeoutMillis);
    HttpConnectionParams.setSoTimeout(params, timeoutMillis);
    HttpUriRequest request = new HttpGet(encodeUrl(url));
    (new AsyncHttp(request, callback)).start();
  }

  /**
   * A quick hack to transform a string into an RFC 3986 compliant URL.
   *
   * TODO: Refactor the code to stop passing URLs around as strings, to eliminate the need for
   * this broken hack.
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
      throw new AssertionError(e);  // Impossible.
    }
    return tmp.toString();
  }
}
