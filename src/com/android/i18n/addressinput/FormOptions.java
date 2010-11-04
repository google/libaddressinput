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

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

/**
 * Configuration Options that can be used by Address Display components for things like show/hide
 * fields or make them readonly. By default, all the fields are visible and editable.
 *
 * <p>Also, provides the ability to add additional required fields, for e.g. {@link
 * AddressField#RECIPIENT}.
 */
public class FormOptions {

    private final String mBaseId;

    private final EnumSet<AddressField> mHiddenFields;

    private final EnumSet<AddressField> mReadonlyFields;

    private final EnumSet<AddressField> mRequiredFields;

    private final EnumMap<AddressField, String> mCustomLabels =
            new EnumMap<AddressField, String>(AddressField.class);

    private final Map<String, AddressField[]> mOverrideFieldOrder =
            new HashMap<String, AddressField[]>();

    private final EnumMap<AddressField, Integer> mMaxLengths =
            new EnumMap<AddressField, Integer>(AddressField.class);

    private final String mServerUrl;

    private FormOptions(Builder builder) {
        // copy values from builder
        mBaseId = builder.mBaseId;
        mHiddenFields = EnumSet.copyOf(builder.mHiddenFields);
        mReadonlyFields = EnumSet.copyOf(builder.mReadonlyFields);
        mRequiredFields = EnumSet.copyOf(builder.mRequiredFields);
        mCustomLabels.putAll(builder.mCustomLabels);
        mOverrideFieldOrder.putAll(builder.mOverrideFieldOrder);
        mMaxLengths.putAll(builder.mMaxLengths);
        mServerUrl = builder.mServerUrl;
    }

    /**
     * Gets base ID of the address form. Default is "addressform".
     */
    String getBaseId() {
        return mBaseId;
    }

    boolean isHidden(AddressField field) {
        return mHiddenFields.contains(field);
    }

    boolean isReadonly(AddressField field) {
        return mReadonlyFields.contains(field);
    }

    boolean isRequired(AddressField field) {
        return mRequiredFields.contains(field);
    }

    EnumSet<AddressField> getRequiredFields() {
        return mRequiredFields;
    }

    /**
     * Gets the customized label for the {@code field}, or returns null if none.
     */
    String getCustomLabel(AddressField field) {
        return mCustomLabels.get(field);
    }

    /**
     * Gets the URL of the Address Data Server.
     */
    String getUrl() {
        return mServerUrl;
    }

    /**
     * Gets the overridden field orders with their corresponding region code. Returns null if field
     * orders for {@code regionCode} is not specified.
     */
    AddressField[] getCustomFieldOrder(String regionCode) {
        if (regionCode == null) {
            throw new RuntimeException("regionCode cannot be null.");
        }
        return mOverrideFieldOrder.get(regionCode);
    }

    /**
     * Gets the customized max length for the {@code field}, or null if none.
     */
    Integer getCustomMaxLength(AddressField field) {
        return mMaxLengths.get(field);
    }

    /**
     * Class to build the form, specifying the attributes for each field.
     */
    public static class Builder {

        private String mBaseId = "addressform";

        private final EnumSet<AddressField> mRequiredFields =
                EnumSet.noneOf(AddressField.class);

        private final EnumSet<AddressField> mHiddenFields =
                EnumSet.noneOf(AddressField.class);

        private final EnumSet<AddressField> mReadonlyFields =
                EnumSet.noneOf(AddressField.class);

        private final EnumMap<AddressField, String> mCustomLabels =
                new EnumMap<AddressField, String>(AddressField.class);

        private final Map<String, AddressField[]> mOverrideFieldOrder =
                new HashMap<String, AddressField[]>();

        private final EnumMap<AddressField, Integer> mMaxLengths =
                new EnumMap<AddressField, Integer>(AddressField.class);

        /**
         * Uses the default server URL from CacheData.
         */
        private String mServerUrl = new CacheData().getUrl();

        /**
         * Sets the base ID of the address form.
         */
        public Builder baseId(String baseId) {
            if (baseId == null) {
                throw new RuntimeException("baseId cannot be null.");
            }
            mBaseId = baseId;
            return this;
        }

        public Builder hide(AddressField field) {
            if (field == null) {
                throw new RuntimeException("AddressField field cannot be null.");
            }
            mHiddenFields.add(field);
            return this;
        }

        /**
         * Make a field read-only.
         */
        public Builder readonly(AddressField field) {
            if (field == null) {
                throw new RuntimeException("AddressField field cannot be null.");
            }
            mReadonlyFields.add(field);
            return this;
        }

        /**
         * Make a field required.
         */
        public Builder required(AddressField field) {
            if (field == null) {
                throw new RuntimeException("AddressField field cannot be null.");
            }
            mRequiredFields.add(field);
            return this;
        }

        /**
         * Customizes label for an {@code AddressField}.
         */
        public Builder customizeLabel(AddressField field, String label) {
            if (field == null) {
                throw new RuntimeException("AddressField field cannot be null.");
            }
            if (label == null) {
                throw new RuntimeException("Label cannot be null.");
            }
            mCustomLabels.put(field, label);
            return this;
        }

        /**
         * Sets the field order for a region code. The order you set here will override the
         * predefined one. For example, you can set field order for US to be first {@code
         * AddressField#ORGANIZATION} then {@code AddressField#RECIPIENT}. Repeated address fields
         * in {@code fields} are not allowed. Size of {@code fields} has to be larger than one.
         * Input {@code fields} can be partial or even contain field not needed in the specified
         * {@code regionCode}. For example, German addresses contain the following fields
         * (in order):<br/>
           {@link AddressField#RECIPIENT}, {@link AddressField#ORGANIZATION}, {@link
         * AddressField#STREET_ADDRESS}, {@link AddressField#POSTAL_CODE}, {@link
         * AddressField#LOCALITY}. <br/>
         *
         * <p>With the following call: <br/>
         *
         * customizeFieldOrder("DE", AddressField.ORGANIZATION, AddressField.RECIPIENT,
         * AddressField.ADMIN_AREA);
         *
         * <p>Field order for Germany will become: <br/> {@link AddressField#ORGANIZATION}, {@link
         * AddressField#RECIPIENT}, {@link AddressField#STREET_ADDRESS}, {@link
         * AddressField#POSTAL_CODE}, {@link AddressField#LOCALITY}. </p>
         *
         * <p>Notice that:<br/> <ol> <li>{@link AddressField#ORGANIZATION} comes before {@link
         * AddressField#RECIPIENT} after reordering.</li>
         * <li>Fields not specified stays the same.</li>
         * <li>{@link AddressField#ADMIN_AREA} is specified but since it is not in German address
         * format, it is simpled neglected.</li> </ol>
         *
         * @param fields the overridden field order.
         */
        public Builder customizeFieldOrder(String regionCode, AddressField... fields) {
            if (regionCode == null) {
                throw new RuntimeException("regionCode cannot be null.");
            }
            if (fields == null) {
                throw new RuntimeException("Fields cannot be null.");
            }
            if (fields.length <= 1) {
                throw new RuntimeException("There must be more than one field.");
            }
            HashSet<AddressField> checkList = new HashSet<AddressField>();
            AddressField[] f = new AddressField[fields.length];
            int i = 0;
            for (AddressField field : fields) {
                // Can't contain repeated address fields.
                if (checkList.contains(field)) {
                    throw new RuntimeException("Address fields cannot be repeated.");
                }
                checkList.add(field);
                f[i] = field;
                i++;
            }
            mOverrideFieldOrder.put(regionCode, f);
            return this;
        }

        /**
         * Sets the URL of address data server. {@code url} cannot be null. This url will override
         * the default address server url.
         */
        public Builder setUrl(String url) {
            if (url == null) {
                throw new RuntimeException("Can't set address server URL to null.");
            }
            mServerUrl = url;
            return this;
        }

        /**
         * Customizes max length for a {@code AddressField}.
         */
        public Builder customizeMaxLength(AddressField field, int maxLength) {
            if (field == null) {
                throw new RuntimeException("AddressField field cannot be null.");
            }
            mMaxLengths.put(field, maxLength);
            return this;
        }

        public FormOptions build() {
            return new FormOptions(this);
        }
    }
}
