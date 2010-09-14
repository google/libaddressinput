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

import java.util.concurrent.TimeoutException;

import junit.framework.TestCase;

public class CacheDataTest extends TestCase {
  private CacheData cache;

  private static final String DELIM = "~";

  private static final String CANADA_KEY = "data/CA";

  private static final String US_KEY = "data/US";

  private static final String CALIFORNIA_KEY = "data/US/CA";

  private static final String RANDOM_COUNTRY_KEY = "data/asIOSDxcowW";

  private static final String EXAMPLE_LOCAL_US_KEY = "examples/US/local"
      + "/_default";

  // Data key for Da-an District, Taipei Taiwan
  private static final String TW_KEY = "data/TW/\u53F0\u5317\u5E02/\u5927"
      + "\u5B89\u5340";

  private static final String FRANCE_KEY = "data/FR";

  private static Integer listenerInvokeCount = 0;

  private static boolean reachedMaxCount = false;

  public void setUp() {
    cache = new CacheData();
  }

  public void testSimpleFetching() {
    final LookupKey key = new LookupKey.Builder(CANADA_KEY).build();

    delayTestFinish(10000);

    cache.fetchDynamicData(key, null, new DataLoadListener() {
      boolean beginCalled = false;

      public void dataLoadingBegin() {
        beginCalled = true;
      }

      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called", beginCalled);
        JsoMap map = cache.getObj(CANADA_KEY);

        assertTrue(map.containsKey(AddressDataKey.ID.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.NAME.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.LANG.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.UPPER.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.ZIPEX.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.ZIP.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.FMT.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.LANGUAGES.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.SUB_KEYS.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.SUB_NAMES.name()
            .toLowerCase()));
        assertFalse(map.containsKey(AddressDataKey.SUB_LNAMES.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.SUB_ZIPS.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.POSTURL.name()
            .toLowerCase()));

        int namesSize = map.get(AddressDataKey.SUB_NAMES.name()
            .toLowerCase()).split(DELIM).length;
        int keysSize = map.get(AddressDataKey.SUB_KEYS.name()
            .toLowerCase()).split(DELIM).length;

        assertEquals("Expect 13 states in Canada.", 13, namesSize);
        assertEquals(namesSize, keysSize);
        finishTest();
      }
    });
  }

  public void testFetchingTaiwanData() {
    final LookupKey key = new LookupKey.Builder(TW_KEY).build();

    delayTestFinish(10000);

    cache.fetchDynamicData(key, null, new DataLoadListener() {
      boolean beginCalled = false;

      public void dataLoadingBegin() {
        beginCalled = true;
      }

      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called", beginCalled);

        JsoMap map = cache.getObj(TW_KEY);

        assertTrue(map.containsKey(AddressDataKey.ID.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.KEY.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.LNAME.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.LANG.name()
            .toLowerCase()));
        assertTrue(map.containsKey(AddressDataKey.ZIP.name()
            .toLowerCase()));
        assertFalse(map.containsKey(AddressDataKey.FMT.name()
            .toLowerCase()));
        assertFalse(map.containsKey(AddressDataKey.SUB_KEYS.name()
            .toLowerCase()));
        assertFalse(map.containsKey(AddressDataKey.SUB_NAMES.name()
            .toLowerCase()));
        assertFalse(map.containsKey(AddressDataKey.SUB_LNAMES.name()
            .toLowerCase()));
        assertFalse(map.containsKey(AddressDataKey.SUB_ZIPS.name()
            .toLowerCase()));

        // Da-an district.
        assertEquals("\u5927\u5B89\u5340", map.get(AddressDataKey.KEY.name()
            .toLowerCase()));

        assertEquals("zh-hant", map.get(AddressDataKey.LANG.name()
            .toLowerCase()));

        finishTest();
      }
    });
  }

  public void testFetchingExamples() {
    final LookupKey key = new LookupKey.Builder(EXAMPLE_LOCAL_US_KEY).build();

    delayTestFinish(10000);

    cache.fetchDynamicData(key, null, new DataLoadListener() {
      boolean beginCalled = false;

      public void dataLoadingBegin() {
        beginCalled = true;
      }

      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called", beginCalled);

        JsoMap map = cache.getObj(EXAMPLE_LOCAL_US_KEY);
        assertTrue(map.containsKey(AddressDataKey.NAME.name().toLowerCase()));
        finishTest();
      }
    });
  }

  public void testFetchingOneKeyManyTimes() {
    final LookupKey key = new LookupKey.Builder(CALIFORNIA_KEY).build();
    final int maxCount = 10;

    class CounterListener implements DataLoadListener {
      public void dataLoadingBegin() {
        listenerInvokeCount++;
        if (listenerInvokeCount == maxCount) {
          reachedMaxCount = true;
        }
        assertTrue(
            "CounterListener's dataLoadingBegin should not be invoked for more "
            + "than " + maxCount + " times",
            listenerInvokeCount <= maxCount);
      }

      public void dataLoadingEnd() {
        listenerInvokeCount--;
        assertTrue(listenerInvokeCount >= 0);
        if (listenerInvokeCount == 0) {
          assertTrue(
              "Expect to see key " + key + " cached when CounterListener's "
              + " dataLoadingEnd is invoked",
              cache.containsKey(key.toString()));
          assertTrue(
              "Expect CounterListener's dataLoadingEnd to be triggered "
              + maxCount + " times in total",
              reachedMaxCount);
          finishTest();
        }
      }
    }

    delayTestFinish(10000);

    for (int i = 0; i < maxCount; ++i) {
      cache.fetchDynamicData(key, null, new CounterListener());
    }

    // Null listeners should not affect results.
    cache.fetchDynamicData(key, null, null);
    cache.fetchDynamicData(key, null, null);
    cache.fetchDynamicData(key, null, null);
  }

  public void testFetchAgainRighAfterOneFetchStart() {
    final LookupKey key = new LookupKey.Builder(US_KEY).build();

    delayTestFinish(10000);

    cache.fetchDynamicData(key, null, null);

    cache.fetchDynamicData(key, null, new DataLoadListener() {
      boolean beginCalled = false;

      public void dataLoadingBegin() {
        assertFalse("data for key " + key + " should not be fetched yet",
            cache.containsKey(key.toString()));
        beginCalled = true;
      }

      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called", beginCalled);

        assertTrue(cache.containsKey(key.toString()));

        cache.fetchDynamicData(key, null, new DataLoadListener() {
          boolean beginCalled2 = false;

          public void dataLoadingBegin() {
            beginCalled2 = true;
          }

          public void dataLoadingEnd() {
            assertTrue("dataLoadingBegin should be called", beginCalled2);

            assertTrue(cache.containsKey(key.toString()));
            finishTest();
          }
        });
      }
    });
  }

  public void testInvalidKey() {
    final LookupKey key = new LookupKey.Builder(RANDOM_COUNTRY_KEY).build();

    delayTestFinish(15000);

    cache.fetchDynamicData(key, null, new DataLoadListener() {
      boolean beginCalled = false;

      public void dataLoadingBegin() {
        beginCalled = true;
      }

      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called", beginCalled);
        assertFalse(cache.containsKey(key.toString()));

        finishTest();
      }
    });
  }

  public void testSetUrl() {
    final LookupKey key = new LookupKey.Builder(FRANCE_KEY).build();
    final String originalUrl = cache.getUrl();

    assertFalse(FRANCE_KEY + " should not be in the cache. Do you request "
        + " it before this test?", cache.containsKey(key.toString()));

    delayTestFinish(10000);
    // Something that is not an URL.
    cache.setUrl("FDSSfdfdsfasdfadsf");

    cache.fetchDynamicData(key, null, new DataLoadListener() {
      boolean beginCalled = false;

      public void dataLoadingBegin() {
        beginCalled = true;
      }

      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called", beginCalled);
        assertFalse(cache.containsKey(key.toString()));
        cache.setUrl(originalUrl);
        finishTest();
      }
    });
  }

  //
  // Temporary implementation of GWT asynchronous test cases.
  //
  // TODO: Replace with something more sophisticated.
  //

  /**
   * Tracks whether this test is completely done.
   */
  private boolean testIsFinished;

  /**
   * The system time in milliseconds when the test should time out.
   */
  private long testTimeoutMillis;

  /**
   * Put the current test in asynchronous mode.
   *
   * @param timeoutMillis Wait this long before failing the test for time out.
   */
  private void delayTestFinish(int timeoutMillis) {
    testTimeoutMillis = System.currentTimeMillis() + timeoutMillis;
  }

  /**
   * Cause this test to succeed during asynchronous mode.
   */
  private void finishTest() {
    testIsFinished = true;
    synchronized (this) {
      notify();
    }
  }

  @Override
  protected void runTest() throws Throwable {
    testIsFinished = false;
    testTimeoutMillis = 0;
    super.runTest();

    if (testTimeoutMillis > 0) {
      long timeoutMillis = testTimeoutMillis - System.currentTimeMillis();
      if (timeoutMillis > 0) {
        synchronized (this) {
          wait(timeoutMillis);
        }
      }
      if (!testIsFinished) {
        throw new TimeoutException("Waited " + timeoutMillis + " ms!");
      }
    }
  }
}
