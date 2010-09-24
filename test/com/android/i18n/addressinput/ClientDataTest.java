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

public class ClientDataTest extends AsyncTestCase {
  private ClientData client;

  public void setUp() {
    client = new ClientData(new CacheData());
  }

  public void testGet() {
      AddressVerificationNodeData data = client.get("data");
      assertNotNull(data);
  }
  
  public void testGet2() {
      AddressVerificationNodeData data;
      
      data = client.get("data");
      assertNotNull(data);
      
      data = client.get("data");
      assertNotNull(data);
  }
  
  public void testPrefetchCountry() {
    delayTestFinish(60000);

    client.prefetchCountry("TW", new DataLoadListener() {
      boolean beginCalled = false;

      public void dataLoadingBegin() {
        beginCalled = true;
      }

      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called", beginCalled);
        // Currently this test only tests that the execution doesn't crash and eventually
        // terminates. TODO: Write test cases to verify that correct data is loaded.
        finishTest();
      }
    });
  }
}
