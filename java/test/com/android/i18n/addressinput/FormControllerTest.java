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

import com.android.i18n.addressinput.LookupKey.KeyType;
import com.android.i18n.addressinput.testing.AsyncTestCase;

import java.util.List;

/**
 * Basic Tests for {@link FormController}.
 */
public class FormControllerTest extends AsyncTestCase {

  private ClientData clientData;

  private static final AddressData US_ADDRESS = new AddressData.Builder().setCountry("US").build();

  private static final AddressData US_CA_ADDRESS = new AddressData.Builder()
      .setCountry("US")
      .setAdminArea("CA")
      .setLocality("Mt View")
      .setAddressLine1("1098 Alta Ave")
      .setPostalCode("94043")
      .build();

  @Override
  public void setUp() {
    clientData = new ClientData(new CacheData());
  }

  public void testRequestDataForAddress() {
    final FormController controller = new FormController(clientData, "en", "US");

    delayTestFinish(15000);

    controller.requestDataForAddress(US_CA_ADDRESS, new DataLoadListener() {
      boolean beginCalled = false;
      @Override
      public void dataLoadingBegin() {
        beginCalled = true;
      }

      @Override
      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called before dataLoadingEnd",
            beginCalled);
        LookupKey usCaMtvKey = new LookupKey.Builder(KeyType.DATA)
            .setAddressData(US_CA_ADDRESS).build();
        LookupKey usKey = usCaMtvKey.getKeyForUpperLevelField(
            AddressField.COUNTRY);
        LookupKey usCaKey = usCaMtvKey.getKeyForUpperLevelField(
            AddressField.ADMIN_AREA);
        assertNotNull("key should be data/US/CA", usCaKey);
        assertNotNull("key should be data/US/CA/Mt View", usCaMtvKey);
        assertNotNull(clientData.get(usKey.toString()));
        assertNotNull(clientData.get(usCaKey.toString()));
        assertNull(clientData.get(usCaMtvKey.toString()));
        finishTest();
      }
    });
  }

  public void testRequestDataForBadAddress() {
    final AddressData address = new AddressData.Builder(US_CA_ADDRESS)
        .setAdminArea("FOOBAR")
        .setLocality("KarKar")
        .build();

    final FormController controller = new FormController(clientData, "en", "US");

    delayTestFinish(15000);

    controller.requestDataForAddress(address, new DataLoadListener() {
      boolean beginCalled = false;
      @Override
      public void dataLoadingBegin() {
        beginCalled = true;
      }

      @Override
      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called before dataLoadingEnd",
            beginCalled);
        LookupKey badKey = new LookupKey.Builder(KeyType.DATA)
            .setAddressData(address).build();
        LookupKey usKey = badKey.getKeyForUpperLevelField(AddressField.COUNTRY);

        List<RegionData> rdata = controller.getRegionData(usKey);
        assertTrue(rdata.size() > 0);
        String subkey = rdata.get(0).getKey();
        assertNotNull("Should be the first US state", subkey);
        LookupKey usFirstStateKey =
            new LookupKey.Builder(usKey.toString() + "/" + subkey).build();

        assertNotNull(clientData.get(usKey.toString()));
        assertNotNull(clientData.get(usFirstStateKey.toString()));
        assertNull(clientData.get(badKey.toString()));
        finishTest();
      }
    });
  }

  public void testRequestDataForCountry() {
    final FormController controller = new FormController(clientData, "en", "US");

    delayTestFinish(15000);

    controller.requestDataForAddress(US_ADDRESS, new DataLoadListener() {
      boolean beginCalled = false;
      @Override
      public void dataLoadingBegin() {
        beginCalled = true;
      }

      @Override
      public void dataLoadingEnd() {
        assertTrue("dataLoadingBegin should be called before dataLoadingEnd",
            beginCalled);
        LookupKey usKey = new LookupKey.Builder(KeyType.DATA)
            .setAddressData(US_ADDRESS).build();
        assertNotNull("key should be data/US", usKey);
        List<RegionData> rdata = controller.getRegionData(usKey);
        assertTrue(rdata.size() > 0);
        String subkey = rdata.get(0).getKey();
        assertNotNull("Should be the first US state", subkey);
        LookupKey usFirstStateKey =
            new LookupKey.Builder(usKey.toString() + "/" + subkey).build();
        assertNotNull(clientData.get(usKey.toString()));
        assertNotNull(clientData.get(usFirstStateKey.toString()));
        finishTest();
      }
    });
  }
}
