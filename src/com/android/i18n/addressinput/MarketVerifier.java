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

import com.android.i18n.addressinput.testing.AddressDataMapLoader;

/**
 * Wrapping for used with android market. Use the method
 * verify(AddressData address, AddressProblems problems) to validate
 * AddressData.
 */
public class MarketVerifier extends StandardAddressVerifier {

  public MarketVerifier() {
    super(new FieldVerifier(new AddressVerificationData(AddressDataMapLoader.DATA)));
  }
}
