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

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;

/**
 * Android implementation of AsyncRequestApi.
 * <p>
 * Note that this class uses a thread-per-request approach to asynchronous connections. There are
 * likely to be better ways of doing this (and even if not, this implementation suffers from several
 * issues regarding interruption and cancellation). Ultimately this class should be revisited and
 * most likely rewritten.
 */
// TODO: Reimplement this class according to current best-practice for asynchronous requests.
public class AndroidAsyncRequestApi implements AsyncRequestApi {
  /** Simple implementation of asynchronous HTTP GET. */
  private static class AsyncHttp extends Thread {
    private final String requestUrlString;
    private final AsyncCallback callback;
    private final int timeoutMillis;

    protected AsyncHttp(String requestUrlString, AsyncCallback callback, int timeoutMillis) {
      this.requestUrlString = requestUrlString;
      this.callback = callback;
      this.timeoutMillis = timeoutMillis;
    }

    @Override
    public void run() {
      try {
        // While MalformedURLException from URL's constructor is a different kind of error than
        // issues with the HTTP request, we're handling them the same way because the URLs are often
        // generated based on data returned by previous HTTP requests and we need robust, graceful
        // handling of any issues.
        URL url = encodeUrl(requestUrlString);
        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setConnectTimeout(timeoutMillis);
        connection.setReadTimeout(timeoutMillis);

        if (connection.getResponseCode() == HttpURLConnection.HTTP_OK) {
          BufferedReader responseReader = new BufferedReader(
              new InputStreamReader(connection.getInputStream(), "UTF-8"));
          StringBuilder responseJson = new StringBuilder();
          String line;
          while ((line = responseReader.readLine()) != null) {
            responseJson.append(line);
          }
          responseReader.close();
          callback.onSuccess(JsoMap.buildJsoMap(responseJson.toString()));
        } else {
          callback.onFailure();
        }
        connection.disconnect();
      } catch (Exception e) {
        callback.onFailure();
      }
    }
  }

  @Override public void requestObject(String url, AsyncCallback callback, int timeoutMillis) {
    (new AsyncHttp(url, callback, timeoutMillis)).start();
  }

  /**
   * A quick hack to transform a string into an RFC 3986 compliant URL.
   *
   * TODO: Refactor the code to stop passing URLs around as strings, to eliminate the need for
   * this broken hack.
   */
  private static URL encodeUrl(String url) throws MalformedURLException {
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
    return new URL(tmp.toString());
  }
}
