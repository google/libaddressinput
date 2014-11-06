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

// TODO: This interface and AddressVerificationData will be
// removed when we have created code for static loading of data without using the
// AddressVerificationData class.
public interface DataSource {
  /**
   * Returns the default JSON data for the given key string (this method should complete immediately
   * and must not trigger any network requests.
   */
  AddressVerificationNodeData getDefaultData(String key);

  /**
   * A <b>blocking</b> method to return the JSON data for the given key string. This method will
   * block the current thread until data is available or until a timeout occurs (at which point the
   * default data will be returned). All networking and failure states are hidden from the caller by
   * this API.
   */
  AddressVerificationNodeData get(String key);
}
