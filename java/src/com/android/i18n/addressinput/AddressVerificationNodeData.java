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

import java.util.Iterator;
import java.util.Map;

/**
 * A map of {@link AddressDataKey}s to JSON strings. Provides data for a single node in the address
 * data hierarchy (for example, "data/US/CA"). Key is an AddressDataKey and the value is the raw
 * string representing that data. This is either a single string, or an array of strings represented
 * as a single string using '~' to separate the elements of the array, depending on the
 * AddressDataKey.
 */
public class AddressVerificationNodeData {

    private final Map<AddressDataKey, String> mMap;

    public AddressVerificationNodeData(Map<AddressDataKey, String> map) {
        Util.checkNotNull("Cannot construct StandardNodeData with null map");
        mMap = map;
    }

    /**
     * Iterates through the map.
     */
    public Iterator<AddressDataKey> iterator() {
        return mMap.keySet().iterator();
    }

    public boolean containsKey(AddressDataKey key) {
        return mMap.containsKey(key);
    }

    /**
     * Gets the value for a particular key in the map.
     */
    public String get(AddressDataKey key) {
        return mMap.get(key);
    }
}
