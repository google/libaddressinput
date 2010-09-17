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
 * Enumerates all the data fields found in the JSON-format address property data.
 */
public enum AddressDataKey {

    /**
     * Identifies the countries for which data is provided.
     */
    COUNTRIES,
    /**
     * Is present with the value "rtl" for countries where the dominant writing system is
     * right-to-left.
     */
    DIR,
    /**
     * Is present with the value "true" for disputed regions within a country. Some clients may wish
     * to not show data for these regions.
     */
    DISPUTED,
    /**
     * The standard format string.  This identifies which fields can be used in the address, along
     * with their order.  This also carries additional information for use in formatting the fields
     * into multiple lines.
     */
    FMT,
    /**
     * Indicates additional limitations on the data for address fields, based upon the enumerated
     * character sets.
     */
    FMTCHARSETS,
    /**
     * Is present with the value "true" for countries that have disputed regions.
     */
    HASDISPUTED,
    /**
     * The unique id of the region, in the form of a path from parent ids to the key.
     */
    ID,
    /**
     * The local (country-specific) ISO 3166-2 ID for this region, if there is one.  This value must
     * be present.
     */
    ISOID,
    /**
     * The key of the region, unique to its parent.  This is the name, if name is not present, or
     * the short name, if name is present.  This value must be present.
     */
    KEY,
    /**
     * The langauge of this data, if known.
     */
    LANG,
    /**
     * The languages used by children of this region, if known.
     */
    LANGUAGES,
    /**
     * The latin format string {@link #FMT} used when a country defines an alternative format for
     * use with the latin script.
     */
    LFMT,
    /**
     * The full latin name {@link #LNAME} present when the latin name has been shortened for length
     * reasons (for example, names of Chinese minority groups are omitted from the lname).
     */
    LFNAME,
    /**
     * The latin name {@link #LFMT} used to present the latin version of the region.
     */
    LNAME,
    /**
     * The local name of the region.  This name is present if different from the key.
     */
    NAME,
    /**
     * Common prefix for postal code (hints that it is not to be entered).
     */
    POSTPREFIX,
    /**
     * A URL to the country's postal address lookup page, if available.
     */
    POSTURL,
    /**
     * Indicates which fields must be present in a valid address.
     */
    REQUIRE,
    /**
     * Indicates the type of the name used for the state (administrative area) field.
     */
    STATE_NAME_TYPE,
    /**
     * Encodes the {@link #DISPUTED} value of all the children of this region. Used by the GWT UI
     * widget.
     */
    SUB_DISPUTEDS,
    /**
     * Encodes the {@link #ISOID} value of all the children of this region. Used by the GWT UI
     * widget.
     */
    SUB_ISOIDS,
    /**
     * Encodes the {@link #KEY} value of all the children of this region. Used by the GWT UI widget.
     */
    SUB_KEYS,
    /**
     * Encodes the {@link #LFNAME} value of all the children of this region. Used by the GWT UI
     * widget.
     */
    SUB_LFNAMES,
    /**
     * Encodes the {@link #LNAME} value of all the children of this region. Used by the GWT UI
     * widget.
     */
    SUB_LNAMES,
    /**
     * Indicates, for each child of this region, whether that child has additional children. Used by
     * the GWT UI widget.
     */
    SUB_MORES,
    /**
     * Encodes the {@link #NAME} value of all the children of this region. Used by the GWT UI
     * widget.
     */
    SUB_NAMES,
    /**
     * Encodes the {@link #XREQUIRE} value of all the children of this region. Used by the GWT UI
     * widget.
     */
    SUB_XREQUIRES,
    /**
     * Encodes the {@link #XZIP} value of all the children of this region. Used by the GWT UI widget.
     */
    SUB_XZIPS,
    /**
     * Encodes the {@link #ZIP} value of all the children of this region. Used by the GWT UI widget.
     */
    SUB_ZIPS,
    /**
     * Encodes the {@link #ZIPEX} value of all the children of this region. Used by the GWT UI
     * widget.
     */
    SUB_ZIPEXS,
    /**
     * Encodes which fields of the address should be in upper case, according the the country's
     * postal office.
     */
    UPPER,
    /**
     * Encodes the {@link #REQUIRE} value for the subtree beneath this region.
     */
    XREQUIRE,
    /**
     * Encodes the {@link #ZIP} value for the subtree beneath this region.
     */
    XZIP,
    /**
     * Encodes the postal code pattern if at the country level, and the postal code prefix if at a
     * level below country.
     */
    ZIP,
    /**
     * Lists example postal codes for this country/region.
     */
    ZIPEX,
    /**
     * Indicates the type of the name used for the zip (postal code) field.
     */
    ZIP_NAME_TYPE;

    /**
     * Returns a field based on its keyname (value in the JSON-format file), or null if no field
     * matches.
     */
    public static AddressDataKey get(String keyname) {
        return map.get(keyname.toLowerCase());
    }

    private static final Map<String, AddressDataKey> map =
            new HashMap<String, AddressDataKey>();

    static {
        for (AddressDataKey f : values()) {
            map.put(f.toString().toLowerCase(), f);
        }
    }
}
