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

/**
 * Android implementation of those parts of the com.google.gwt.jsonp.client.JsonpRequestBuilder
 * class that the CacheData class uses.
 */
public class JsonpRequestBuilder {
  /**
   * Re-implementation of the com.google.gwt.user.client.rpc.AsyncCallback interface.
   */
  public interface AsyncCallback<T> {
    public void onFailure(Throwable caught);
    public void onSuccess(T result);
  }

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
