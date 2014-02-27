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
 * A simple data structure for international postal addresses.
 *
 * Addresses may seem simple, but even within the US there are many quirks (hyphenated street
 * addresses, etc.), and internationally addresses vary a great deal. The most sane and complete in
 * many ways is the OASIS "extensible Address Language", xAL, which is a published and documented
 * XML schema:
 *
 * http://www.oasis-open.org/committees/ciq/download.shtml
 *
 * We have not represented all the fields, but the intent is that if you need to add something, you
 * should follow the OASIS standard.
 *
 * An example address:
 * <p>postalCountry: US</p>
 * <p>addressLine1: 1098 Alta Ave</p>
 * <p>addressLine2:</p>
 * <p>adminstrativeArea: CA</p>
 * <p>locality: Mountain View</p>
 * <p>dependentLocality:</p>
 * <p>postalCode: 94043</p>
 * <p>sortingCode:</p>
 * <p>organization: Google</p>
 * <p>recipient: Chen-Kang Yang</p>
 * <p>language code: en</p>
 *
 * Note that sub-administrative area is NOT used in Address Widget. Sub-administrative Area is
 * second-level administrative subdivision of this country. For examples: US county, IT province, UK
 * county. This level of geo information is not required to fill out address form, therefore is
 * neglected.
 *
 * All values stored in this class are trimmed. Also, if you try to set a field with an empty string
 * or a string consists of only spaces, it will not be set.
 */
public class AddressData {
    // CLDR (Common Locale Data Repository) country code.
    // For example, "US" for United States.
    // (Note: Use "GB", not "UK", for Great Britain)
    private final String mPostalCountry;

    // street street, line 1
    private final String mAddressLine1;

    // street street, line 2
    private final String mAddressLine2;

    // Top-level administrative subdivision of this country.
    // Examples: US state, IT region, UK constituent nation, JP prefecture.
    private final String mAdministrativeArea;

    // Locality. A fuzzy term, but it generally refers to
    // the city/town portion of an address.  In regions of the world where
    // localities are not well defined or do not fit into this structure well
    // (for example, Japan and China), leave locality empty and use
    // addressLine1.
    // Examples: US city, IT comune, UK post town.
    private final String mLocality;

    // Dependent locality or sublocality.  Used for UK dependent localities,
    // or neighborhoods or boroughs in other locations.  If trying to
    // represent a UK double-dependent locality, include both the
    // double-dependent locality and the dependent locality in this field,
    // e.g. "Whaley, Langwith".
    private final String mDependentLocality;

    // Postal Code. values are frequently alphanumeric.
    // Examples: "94043", "94043-1351", "SW1W", "SW1W 9TQ".
    private final String mPostalCode;

    // Sorting code - use is very country-specific.
    // This corresponds to the SortingCode sub-element of the xAL
    // PostalServiceElements element.
    // Examples: FR CEDEX.
    private final String mSortingCode;

    // The firm or organization. This goes at a finer granularity than
    // address lines in the address. Omit if not needed.
    private final String mOrganization;

    // The recipient. This goes at a finer granularity than address lines
    // in the address. Not present in xAL. Omit if not needed.
    private final String mRecipient;

    // Language code of the address. Can be set to null. See its getter and setter
    // for more information.
    private final String mLanguageCode;

    /**
     * Use {@link Builder} to create instances.
     */
    private AddressData(Builder builder) {
        mPostalCountry = builder.mValues.get(AddressField.COUNTRY);
        mAdministrativeArea = builder.mValues.get(AddressField.ADMIN_AREA);
        mLocality = builder.mValues.get(AddressField.LOCALITY);
        mDependentLocality = builder.mValues.get(AddressField.DEPENDENT_LOCALITY);
        mPostalCode = builder.mValues.get(AddressField.POSTAL_CODE);
        mSortingCode = builder.mValues.get(AddressField.SORTING_CODE);
        mOrganization = builder.mValues.get(AddressField.ORGANIZATION);
        mRecipient = builder.mValues.get(AddressField.RECIPIENT);
        mAddressLine1 = builder.mValues.get(AddressField.ADDRESS_LINE_1);
        mAddressLine2 = builder.mValues.get(AddressField.ADDRESS_LINE_2);
        mLanguageCode = builder.mLanguage;
    }

    /**
     * Returns the postal country.
     *
     * <p>The returned value is not user-presentable. For example, {@code getPostalCountry()} may
     * return {@code "GB"}, while addresses in Great Britain should be displayed using "UK".
     */
    public String getPostalCountry() {
        return mPostalCountry;
    }

    public String getAddressLine1() {
        return mAddressLine1;
    }

    public String getAddressLine2() {
        return mAddressLine2;
    }

    /**
     * Returns the top-level administrative subdivision of this country. Different postal countries
     * use different names to refer to their administrative areas. For example, this is called
     * "state" in the United States, "region" in Italy, "constituent nation" in Great Britain, or
     * "prefecture" in Japan.
     */
    public String getAdministrativeArea() {
        return mAdministrativeArea;
    }

    /**
     * Returns the locality. The usage of this field varies by region, but it generally refers to
     * the "city" or "town" of the address. Some regions do not use this field; their address lines
     * are sufficient to locate an address within a sub-administrative area. For example, this is
     * called "city" in the United States, "comune" in Italy, or "post town" in Great Britain.
     */
    public String getLocality() {
        return mLocality;
    }

    /**
     * Returns the dependent locality.
     *
     * <p>This is used for Great Britain dependent localities, or neighborhoods or boroughs in other
     * locations.
     *
     * <p>In cases such as Great Britain, this field may contain a double-dependent locality, such
     * as "Whaley, Langwith".
     */
    public String getDependentLocality() {
        return mDependentLocality;
    }

    /**
     * Returns the firm or organization.
     */
    public String getOrganization() {
        return mOrganization;
    }

    /**
     * Returns the recipient. Examples: "Jesse Wilson" or "Jesse Wilson c/o Apurva Mathad".
     */
    public String getRecipient() {
        return mRecipient;
    }

    /**
     * Returns the country-specific postal code. Examples: "94043", "94043-1351", "SW1W",
     * "SW1W 9TQ".
     */
    public String getPostalCode() {
        return mPostalCode;
    }

    /**
     * Returns the country-specific sorting code. For example, the
     * <a href="http://en.wikipedia.org/wiki/List_of_postal_codes_in_France"> French CEDEX</a>
     */
    public String getSortingCode() {
        return mSortingCode;
    }

    public String getFieldValue(AddressField field) {
        switch (field) {
            case COUNTRY:
                return mPostalCountry;
            case ADMIN_AREA:
                return mAdministrativeArea;
            case LOCALITY:
                return mLocality;
            case DEPENDENT_LOCALITY:
                return mDependentLocality;
            case POSTAL_CODE:
                return mPostalCode;
            case SORTING_CODE:
                return mSortingCode;
            case ADDRESS_LINE_1:
                return mAddressLine1;
            case ADDRESS_LINE_2:
                return mAddressLine2;
            case ORGANIZATION:
                return mOrganization;
            case RECIPIENT:
                return mRecipient;
            default:
                throw new IllegalArgumentException("unrecognized key: " + field);
        }
    }

    /**
     * Returns the language of the text of this address. Languages are used to guide how the address
     * is <a href="http://en.wikipedia.org/wiki/Mailing_address_format_by_country"> formatted for
     * display</a>. The same address may have different {@link AddressData} representations in
     * different languages. For example, the French name of "New Mexico" is "Nouveau-Mexique".
     */
    public String getLanguageCode() {
        return mLanguageCode;
    }

    /**
     * Builder for AddressData
     */
    public static class Builder {

        private final Map<AddressField, String> mValues;

        private String mLanguage = null;

        public Builder() {
            mValues = new HashMap<AddressField, String>();
        }

        /**
         * A constructor that sets address field with input data. Street fields will be normalized
         * in the process. I.e., after copy, there will not be any empty street line in front of
         * non-empty ones. For example, if input data's street line 1 is null but street line 2
         * has a value, this method will copy street line 2's value and set it to street line 1.
         */
        public Builder(AddressData addr) {
            mValues = new HashMap<AddressField, String>();
            set(addr);
        }

        public Builder setCountry(String value) {
            return set(AddressField.COUNTRY, value);
        }

        public Builder setAdminArea(String value) {
            return set(AddressField.ADMIN_AREA, value);
        }

        public Builder setLocality(String value) {
            return set(AddressField.LOCALITY, value);
        }

        public Builder setDependentLocality(String value) {
            return set(AddressField.DEPENDENT_LOCALITY, value);
        }

        public Builder setPostalCode(String value) {
            return set(AddressField.POSTAL_CODE, value);
        }

        public Builder setSortingCode(String value) {
            return set(AddressField.SORTING_CODE, value);
        }

        /**
         * Sets the language code.
         *
         * @param languageCode the language to use, or {@code null} for no specified language.
         */
        public Builder setLanguageCode(String languageCode) {
            this.mLanguage = languageCode;
            return this;
        }

        /**
         * Sets address lines 1 and 2 (if necessary) from a string that may contain multiple lines.
         *
         * <p> Example: Input "  \n   \n1600 Amphitheatre Ave\n\nRoom 122" will set the following
         * values:<br/> line 1: 1600 Amphitheatre Ave<br/> line 2: Room 122<br/> </p>
         *
         * @param value a street string
         */
        public Builder setAddress(String value) {
            setAddressLine1(value);
            return this;
        }

        /**
         * Sets address by copying from input address data. Street fields will be normalized in the
         * process. I.e., after copy, there will not be any empty street lines in front of non-empty
         * ones. For example, if input data's street line 1 is null but street line 2 has a value,
         * this method will copy street line 2's value and set it to street line 1.
         */
        public Builder set(AddressData data) {
            mValues.clear();
            for (AddressField addressField : AddressField.values()) {
                if (addressField == AddressField.STREET_ADDRESS) {
                    continue;  // Do nothing.
                } else {
                    set(addressField, data.getFieldValue(addressField));
                }
            }
            normalizeAddresses();
            setLanguageCode(data.getLanguageCode());
            return this;
        }

        public Builder setAddressLine1(String value) {
            return set(AddressField.ADDRESS_LINE_1, value);
        }

        public Builder setAddressLine2(String value) {
            return set(AddressField.ADDRESS_LINE_2, value);
        }

        public Builder setOrganization(String value) {
            return set(AddressField.ORGANIZATION, value);
        }

        public Builder setRecipient(String value) {
            return set(AddressField.RECIPIENT, value);
        }

        /**
         * Sets an address field with the specified value. If the value is empty (a null string,
         * empty string, or a string that contains only spaces), the original value associated with
         * the field will be removed.
         */
        public Builder set(AddressField field, String value) {
            if (value == null || value.length() == 0) {
                mValues.remove(field);
            } else {
                mValues.put(field, value.trim());
            }
            normalizeAddresses();
            return this;
        }

        public AddressData build() {
            return new AddressData(this);
        }

        /**
         * Parses content of address line fields.
         * If address_line_1 is empty, address_line_2 will be used to populate address_line_1 if
         * possible. If address_line_1 contains a new line, content after the new line will be
         * saved in address_line_2.
         */
        private void normalizeAddresses() {
            String address1 = mValues.get(AddressField.ADDRESS_LINE_1);
            String address2 = mValues.get(AddressField.ADDRESS_LINE_2);
            if (address1 == null || address1.trim().length() == 0) {
                address1 = address2;
                address2 = null;
            }
            if (address1 != null) {
                String[] addressLines = address1.split("\n");
                if (addressLines.length > 1) {
                    address1 = addressLines[0];
                    address2 = addressLines[1];
                }
            }
            mValues.put(AddressField.ADDRESS_LINE_1, address1);
            mValues.put(AddressField.ADDRESS_LINE_2, address2);
        }
    }
}
