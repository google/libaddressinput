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

/**
 * A simple implementation of ClientCacheManager which doesn't do any caching on its own.
 */
public class SimpleClientCacheManager implements ClientCacheManager {
  // URL to get public address data.
  private static final String PUBLIC_ADDRESS_SERVER = "http://i18napis.appspot.com/address";

  @Override
  public String get(String key) {
    return "";
  }

  @Override
  public void put(String key, String data) {
  }

  @Override
  public String getAddressServerUrl() {
    return PUBLIC_ADDRESS_SERVER;
  }
}
