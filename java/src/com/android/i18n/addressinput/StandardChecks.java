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
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Loader for a map defining the standard checks to perform on AddressFields.
 */
public class StandardChecks {

    private StandardChecks() {
    }

    public static final Map<AddressField, List<AddressProblemType>> PROBLEM_MAP;

    static {
        Map<AddressField, List<AddressProblemType>> map =
                new HashMap<AddressField, List<AddressProblemType>>();

        addToMap(map, AddressField.COUNTRY, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD, AddressProblemType.UNKNOWN_VALUE);
        addToMap(map, AddressField.ADMIN_AREA, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD, AddressProblemType.UNKNOWN_VALUE);
        addToMap(map, AddressField.LOCALITY, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD, AddressProblemType.UNKNOWN_VALUE);
        addToMap(map, AddressField.DEPENDENT_LOCALITY, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD, AddressProblemType.UNKNOWN_VALUE);
        addToMap(map, AddressField.POSTAL_CODE, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD, AddressProblemType.UNRECOGNIZED_FORMAT,
                AddressProblemType.MISMATCHING_VALUE);
        addToMap(map, AddressField.STREET_ADDRESS, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD);
        addToMap(map, AddressField.SORTING_CODE, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD);
        addToMap(map, AddressField.ORGANIZATION, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD);
        addToMap(map, AddressField.RECIPIENT, AddressProblemType.USING_UNUSED_FIELD,
                AddressProblemType.MISSING_REQUIRED_FIELD);

        PROBLEM_MAP = Collections.unmodifiableMap(map);
    }

    private static void addToMap(Map<AddressField, List<AddressProblemType>> map,
            AddressField field,
            AddressProblemType... problems) {
        map.put(field, Collections.unmodifiableList(Arrays.asList(problems)));
    }
}
