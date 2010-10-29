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

import java.util.HashMap;
import java.util.Map;

/**
 * Represents all the known field name types, mapping each to its corresponding AddressField.
 *
 * <p>The field name type provides a category for the name of a field as used in a particular
 * region. For example, in the U.S. POSTAL_CODE is a "zip code" while in the U.K. it is a
 * "postcode".  Note that these are are not translations of "postal code", they are different names
 * for the same address data field as used in different countries/regions. It is these
 * FieldNameTypes that get translated, not the AddressFields.
 *
 * <p>Since the number of FieldNameTypes is far less than the number of countries and address
 * fields, this greatly reduces the number of terms to be translated. For example, instead of
 * translating POSTCODE_AS_USED_IN_UK, POSTCODE_AS_USED_IN_DE, POSTCODE_AS_USED_IN_FR,
 * POSTCODE_AS_USED_IN_US... and so on for all 240 countries, only "postcode" and "zipcode" need to
 * be translated.
 */
enum FieldNameType {
    // COUNTRY
    C_COUNTRY(AddressField.COUNTRY),

    // ADMIN_AREA
    AA_AREA(AddressField.ADMIN_AREA),
    AA_COUNTY(AddressField.ADMIN_AREA),
    AA_DEPARTMENT(AddressField.ADMIN_AREA),
    AA_DISTRICT(AddressField.ADMIN_AREA),
    AA_DO_SI(AddressField.ADMIN_AREA),
    AA_EMIRATE(AddressField.ADMIN_AREA),
    AA_ISLAND(AddressField.ADMIN_AREA),
    AA_PARISH(AddressField.ADMIN_AREA),
    AA_PREFECTURE(AddressField.ADMIN_AREA),
    AA_PROVINCE(AddressField.ADMIN_AREA),
    AA_STATE(AddressField.ADMIN_AREA),

    // LOCALITY
    L_CITY(AddressField.LOCALITY),

    // DEPENDENT_LOCALITY
    DL_DISTRICT(AddressField.DEPENDENT_LOCALITY),

    // ADDRESS
    A_ADDRESS(AddressField.STREET_ADDRESS),

    // POSTCODE
    PC_POSTCODE(AddressField.POSTAL_CODE, "postal"),
    PC_ZIPCODE(AddressField.POSTAL_CODE, "zip"),

    // SORTING_CODE
    SC_CEDEX(AddressField.SORTING_CODE),

    // RECIPIENT
    R_RECIPIENT(AddressField.RECIPIENT),

    // ORGANIZATION
    O_ORGANIZATION(AddressField.ORGANIZATION);

    /**
     * Given a keyname (as used in the JSON data), returns the field name type, or null.
     */
    static FieldNameType get(String keyname) {
        return FIELD_NAME_MAP.get(keyname.toLowerCase());
    }

    /**
     * Returns the field associated with this field name type.
     */
    AddressField field() {
        return mField;
    }

    /**
     * Returns the keyname of this field name type.
     */
    String keyname() {
        return mKeyname;
    }

    private final AddressField mField;

    private final String mKeyname;

    private FieldNameType(AddressField field) {
        mField = field;

        String name = name();
        mKeyname = name.substring(name.indexOf('_') + 1).toLowerCase();
    }

    private FieldNameType(AddressField field, String keyname) {
        mField = field;
        mKeyname = keyname;
    }

    private static final Map<String, FieldNameType> FIELD_NAME_MAP = new HashMap<String, FieldNameType>();

    static {
        for (FieldNameType fc : values()) {
            FIELD_NAME_MAP.put(fc.mKeyname, fc);
        }
    }
}
