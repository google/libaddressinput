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
 * Used by AddressWidget to handle caching in client-specific ways.
 */
public interface ClientCacheManager {
  /** Get the data that is cached for the given key. */
  public String get(String key);
  /** Put the data for the given key into the cache. */
  public void put(String key, String data);
  /** Get the URL of the server that serves address metadata. */
  public String getAddressServerUrl();
}
