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

import java.util.Arrays;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/**
 * Creates an FieldVerifierFactory from an AddressVerificationData.
 */
public class FieldVerifierFactory {
  private static final String TEMP_KEY = "temp";
  
  private final AddressVerificationData data;

  private final Map<String, FieldVerifier> verifierCache;

  private FieldVerifier root;
  
  public FieldVerifierFactory(AddressVerificationData data) {
    this.data = data;
    this.verifierCache = new HashMap<String, FieldVerifier>();
    root = new FieldVerifier(data);
  }

  public FieldVerifier rootVerifier() {
    return root;
  }
}
