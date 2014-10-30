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

import com.android.i18n.addressinput.JsonpRequestBuilder.AsyncCallback;
import com.android.i18n.addressinput.testing.AsyncTestCase;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;

public class JsonpRequestBuilderTest extends AsyncTestCase {
  private JsonpRequestBuilder builder;

  @Override
  public void setUp() {
    builder = new JsonpRequestBuilder();
  }

  public void testRequestObject() throws Exception {
    delayTestFinish(4000);
    builder.setTimeout(2000);

    String url = HttpServer.execute(1000, "{\"id\": \"data\"}");

    builder.requestObject(url, new AsyncCallback<JsoMap>() {
      @Override
      public void onFailure(Throwable caught) {
        fail(caught.toString());
      }

      @Override
      public void onSuccess(JsoMap result) {
        assertNotNull(result);
        assertEquals("data", result.get("id"));
        finishTest();
      }
    });
  }

  public void testSetTimeout() throws Exception {
    delayTestFinish(4000);
    builder.setTimeout(1000);

    String url = HttpServer.execute(2000, "Fubar");

    builder.requestObject(url, new AsyncCallback<JsoMap>() {
      @Override
      public void onFailure(Throwable caught) {
        assertNotNull(caught);
        assertTrue(caught instanceof SocketTimeoutException);
        finishTest();
      }

      @Override
      public void onSuccess(JsoMap result) {
        fail("The request should have timed out.");
      }
    });
  }

  public void testUrlEncoding() throws Exception {
    delayTestFinish(4000);
    builder.setTimeout(2000);

    String urlBase = HttpServer.execute(1000, "{\"id\": \"data\"}");
    String url = urlBase + "address/data/VN/B\u1EAFc K\u1EA1n";

    builder.requestObject(url, new AsyncCallback<JsoMap>() {
      @Override
      public void onFailure(Throwable caught) {
        fail(caught.toString());
      }

      @Override
      public void onSuccess(JsoMap result) {
        assertNotNull(result);
        assertEquals("data", result.get("id"));
        finishTest();
      }
    });
  }

  /**
   * Simple implementation of an HTTP server.
   */
  private static class HttpServer extends Thread {
    /**
     * Start an HTTP server that will serve one request and then terminate.
     *
     * @param timeoutMillis
     *            Wait this long before answering a request.
     * @param response
     *            Reply to any request with this response.
     * @return The URL to the server.
     * @throws IOException
     */
    public static String execute(long timeoutMillis, String response) throws IOException {
      HttpServer server = new HttpServer(timeoutMillis, response);
      server.start();
      return "http://localhost:" + server.serverSocket.getLocalPort() + "/";
    }

    @Override
    public void run() {
      try {
        Socket clientSocket = serverSocket.accept();
        try {
          synchronized (this) {
            wait(waitMillis);
          }
        } catch (InterruptedException e) {
          throw new RuntimeException(e);
        }
        InputStream inputStream = clientSocket.getInputStream();
        inputStream.read(new byte[1024]);  // Discard input.
        OutputStream outputStream = clientSocket.getOutputStream();
        outputStream.write(response);
        outputStream.close();
        inputStream.close();
        clientSocket.close();
        serverSocket.close();
      } catch (IOException e) {
        throw new RuntimeException(e);
      }
    }

    private HttpServer(long waitMillis, String response) throws IOException {
      this.waitMillis = waitMillis;
      this.response = (HEADER + response).getBytes();
      serverSocket = new ServerSocket(0);
    }

    private long waitMillis;
    private byte[] response;
    private ServerSocket serverSocket;

    private static final String HEADER = "HTTP/1.0 200 OK\nContent-Type: text/plain\n\n";
  }
}
