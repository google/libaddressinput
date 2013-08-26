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
import java.util.Map;

/**
 * A builder for creating keys that are used to lookup data in the local cache and fetch data from
 * the server. There are two key types: {@code KeyType#DATA} or {@code KeyType#EXAMPLES}.
 *
 * <p> The {@code KeyType#DATA} key is built based on a universal Address hierarchy, which is:<br>
 *
 * {@code AddressField#Country} -> {@code AddressField#ADMIN_AREA} -> {@code AddressField#Locality}
 * -> {@code AddressField#DEPENDENT_LOCALITY} </p>
 *
 * <p> The {@code KeyType#EXAMPLES} key is built with the following format:<br>
 *
 * {@code AddressField#Country} -> {@code ScriptType} -> language. </p>
 */
final class LookupKey {

    /**
     * Key types. Address Widget organizes address info based on key types. For example, if you want
     * to know how to verify or format an US address, you need to use {@link KeyType#DATA} to get
     * that info; if you want to get an example address, you use {@link KeyType#EXAMPLES} instead.
     */
    enum KeyType {

        /**
         * Key type for getting address data.
         */
        DATA,
        /**
         * Key type for getting examples.
         */
        EXAMPLES
    }

    /**
     * Script types. This is used for countries that do not use Latin script, but accept it for
     * transcribing their addresses. For example, you can write a Japanese address in Latin script
     * instead of Japanese:
     *
     * <p> 7-2, Marunouchi 2-Chome, Chiyoda-ku, Tokyo 100-8799 </p>
     *
     * Notice that {@link ScriptType} is based on country/region, not language.
     */
    enum ScriptType {

        /**
         * The script that uses Roman characters like ABC (as opposed to scripts like Cyrillic or
         * Arabic).
         */
        LATIN,

        /**
         * Local scripts. For Japan, it's Japanese (including Hiragana, Katagana, and Kanji); For
         * Saudi Arabia, it's Arabic. Notice that for US, the local script is actually Latin script
         * (The same goes for other countries that use Latin script). For these countries, we do not
         * provide two set of data (Latin and local) since they use only Latin script. You have to
         * specify the {@link ScriptType} as local instead Latin.
         */
        LOCAL
    }

    /**
     * The universal address hierarchy. Notice that sub-administrative area is neglected here since
     * it is not required to fill out address form.
     */
    private static final AddressField[] HIERARCHY = {
            AddressField.COUNTRY,
            AddressField.ADMIN_AREA,
            AddressField.LOCALITY,
            AddressField.DEPENDENT_LOCALITY};

    private static final String SLASH_DELIM = "/";

    private static final String DASH_DELIM = "--";

    private static final String DEFAULT_LANGUAGE = "_default";

    private final KeyType mKeyType;

    private final ScriptType mScriptType;

    // Values for hierarchy address fields.
    private final Map<AddressField, String> mNodes;

    private final String mKeyString;

    private final String mLanguageCode;

    private LookupKey(Builder builder) {
        this.mKeyType = builder.keyType;
        this.mScriptType = builder.script;
        this.mNodes = builder.nodes;
        this.mLanguageCode = builder.languageCode;
        this.mKeyString = getKeyString();
    }

    /**
     * Gets lookup key for the input address field. This method does not allow key with key type of
     * {@link KeyType#EXAMPLES}.
     *
     * @param field a field in the address hierarchy.
     * @return key of the specified address field. If address field is not in the hierarchy, or is
     *         more granular than the current key has, returns null. For example, if your current
     *         key is "data/US" (down to country level), and you want to get the key for Locality
     *         (more granular than country), it will return null.
     */
    LookupKey getKeyForUpperLevelField(AddressField field) {
        if (mKeyType != KeyType.DATA) {
            // We only support getting the parent key for the data key type.
            throw new RuntimeException("Only support getting parent keys for the data key type.");
        }
        Builder newKeyBuilder = new Builder(this);

        boolean removeNode = false;
        boolean fieldInHierarchy = false;
        for (AddressField hierarchyField : HIERARCHY) {
            if (removeNode) {
                if (newKeyBuilder.nodes.containsKey(hierarchyField)) {
                    newKeyBuilder.nodes.remove(hierarchyField);
                }
            }
            if (hierarchyField == field) {
                if (!newKeyBuilder.nodes.containsKey(hierarchyField)) {
                    return null;
                }
                removeNode = true;
                fieldInHierarchy = true;
            }
        }

        if (!fieldInHierarchy) {
            return null;
        }

        newKeyBuilder.languageCode = mLanguageCode;
        newKeyBuilder.script = mScriptType;

        return newKeyBuilder.build();
    }

    /**
     * Returns the string value of a field in a key for a particular
     * AddressField. For example, for the key "data/US/CA" and the address
     * field AddressField.COUNTRY, "US" would be returned. Returns an empty
     * string if the key does not have this field in it.
     */
    String getValueForUpperLevelField(AddressField field) {
        // First, get the key for this field.
        LookupKey key = getKeyForUpperLevelField(field);
        // Now we know the last value in the string is the value for this field.
        if (key != null) {
            String keyString = key.toString();
            int lastSlashPosition = keyString.lastIndexOf(SLASH_DELIM);
            if (lastSlashPosition > 0 && lastSlashPosition != keyString.length()) {
                return keyString.substring(lastSlashPosition + 1);
            }
        }
        return "";
    }

    /**
     * Gets parent key for data key. For example, parent key for "data/US/CA" is "data/US". This
     * method does not allow key with key type of {@link KeyType#EXAMPLES}.
     */
    LookupKey getParentKey() {
        if (mKeyType != KeyType.DATA) {
            throw new RuntimeException("Only support getting parent keys for the data key type.");
        }
        // Root key's parent should be null.
        if (!mNodes.containsKey(AddressField.COUNTRY)) {
            return null;
        }

        Builder parentKeyBuilder = new Builder(this);
        AddressField mostGranularField = AddressField.COUNTRY;

        for (AddressField hierarchyField : HIERARCHY) {
            if (!mNodes.containsKey(hierarchyField)) {
                break;
            }
            mostGranularField = hierarchyField;
        }
        parentKeyBuilder.nodes.remove(mostGranularField);
        return parentKeyBuilder.build();
    }

    KeyType getKeyType() {
        return mKeyType;
    }

    /**
     * Gets a key in string format. E.g., "data/US/CA".
     */
    private String getKeyString() {
        StringBuilder keyBuilder = new StringBuilder(mKeyType.name().toLowerCase());

        if (mKeyType == KeyType.DATA) {
            for (AddressField field : HIERARCHY) {
                if (!mNodes.containsKey(field)) {
                    break;
                }
                if (field == AddressField.COUNTRY && mLanguageCode != null) {
                    keyBuilder.append(SLASH_DELIM)
                            .append(mNodes.get(field)).append(DASH_DELIM)
                            .append(mLanguageCode);
                } else {
                    keyBuilder.append(SLASH_DELIM).append(mNodes.get(field));
                }
            }
        } else {
            if (mNodes.containsKey(AddressField.COUNTRY)) {
                // Example key. E.g., "examples/TW/local/_default".
                keyBuilder.append(SLASH_DELIM).append(mNodes.get(AddressField.COUNTRY))
                        .append(SLASH_DELIM).append(mScriptType.name().toLowerCase())
                        .append(SLASH_DELIM).append(DEFAULT_LANGUAGE);
            }
        }

        return keyBuilder.toString();
    }

    /**
     * Gets a lookup key as a plain text string., e.g., "data/US/CA".
     */
    @Override
    public String toString() {
        return mKeyString;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if ((obj == null) || (obj.getClass() != this.getClass())) {
            return false;
        }

        return ((LookupKey) obj).toString().equals(mKeyString);
    }

    @Override
    public int hashCode() {
        return mKeyString.hashCode();
    }

    static boolean hasValidKeyPrefix(String key) {
        for (KeyType type : KeyType.values()) {
            if (key.startsWith(type.name().toLowerCase())) {
                return true;
            }
        }
        return false;
    }

    /**
     * Builds lookup keys.
     */
    static class Builder {

        private KeyType keyType;

        // Default to LOCAL script.

        private ScriptType script = ScriptType.LOCAL;

        private Map<AddressField, String> nodes = new EnumMap<AddressField, String>(
                AddressField.class);

        private String languageCode;

        /**
         * Creates a new builder for the specified key type. keyType cannot be null.
         */
        Builder(KeyType keyType) {
            this.keyType = keyType;
        }

        /**
         * Creates a new builder for the specified key. oldKey cannot be null.
         */
        Builder(LookupKey oldKey) {
            this.keyType = oldKey.mKeyType;
            this.script = oldKey.mScriptType;
            this.languageCode = oldKey.mLanguageCode;
            for (AddressField field : HIERARCHY) {
                if (!oldKey.mNodes.containsKey(field)) {
                    break;
                }
                this.nodes.put(field, oldKey.mNodes.get(field));
            }
        }

        /**
         * Builds the {@link LookupKey} with the input key string. Input string has to represent
         * either a {@link KeyType#DATA} key or a {@link KeyType#EXAMPLES} key. Also, key hierarchy
         * deeper than {@link AddressField#DEPENDENT_LOCALITY} is not allowed. Notice that if any
         * node in the hierarchy is empty, all the descendant nodes' values will be neglected. For
         * example, input string "data/US//Mt View" will become "data/US".
         *
         * @param keyString e.g., "data/US/CA"
         */
        Builder(String keyString) {
            String[] parts = keyString.split(SLASH_DELIM);
            // Check some pre-conditions.
            if (!parts[0].equals(KeyType.DATA.name().toLowerCase()) &&
                    !parts[0].equals(KeyType.EXAMPLES.name().toLowerCase())) {
                throw new RuntimeException("Wrong key type: " + parts[0]);
            }
            if (parts.length > HIERARCHY.length + 1) {
                throw new RuntimeException(
                        "input key '" + keyString + "' deeper than supported hierarchy");
            }
            if (parts[0].equals("data")) {
                keyType = KeyType.DATA;

                // Parses country and language info.
                if (parts.length > 1) {
                    String substr = Util.trimToNull(parts[1]);
                    if (substr.contains(DASH_DELIM)) {
                        String[] s = substr.split(DASH_DELIM);
                        if (s.length != 2) {
                            throw new RuntimeException(
                                    "Wrong format: Substring should be country "
                                            + "code--language code");
                        }
                        substr = s[0];
                        languageCode = s[1];
                    }
                    this.nodes.put(HIERARCHY[0], substr);
                }

                // Parses sub-country info.
                if (parts.length > 2) {
                    for (int i = 2; i < parts.length; ++i) {
                        String substr = Util.trimToNull(parts[i]);
                        if (substr == null) {
                            break;
                        }
                        this.nodes.put(HIERARCHY[i - 1], substr);
                    }
                }
            } else if (parts[0].equals("examples")) {
                keyType = KeyType.EXAMPLES;

                // Parses country info.
                if (parts.length > 1) {
                    this.nodes.put(AddressField.COUNTRY, parts[1]);
                }

                // Parses script types.
                if (parts.length > 2) {
                    String scriptStr = parts[2];
                    if (scriptStr.equals("local")) {
                        this.script = ScriptType.LOCAL;
                    } else if (scriptStr.equals("latin")) {
                        this.script = ScriptType.LATIN;
                    } else {
                        throw new RuntimeException("Script type has to be either latin or local.");
                    }
                }

                // Parses language code. Example: "zh_Hant" in
                // "examples/TW/local/zH_Hant".
                if (parts.length > 3 && !parts[3].equals(DEFAULT_LANGUAGE)) {
                    languageCode = parts[3];
                }
            }
        }

        Builder setLanguageCode(String languageCode) {
            this.languageCode = languageCode;
            return this;
        }

        /**
         * Sets key using {@link AddressData}. Notice that if any node in the hierarchy is empty,
         * all the descendant nodes' values will be neglected. For example, the following address
         * misses {@link AddressField#ADMIN_AREA}, thus its data key will be "data/US".
         *
         * <p> country: US<br> administrative area: null<br> locality: Mt. View </p>
         */
        Builder setAddressData(AddressData data) {
            languageCode = data.getLanguageCode();
            if (languageCode != null) {
                if (Util.isExplicitLatinScript(languageCode)) {
                    script = ScriptType.LATIN;
                }
            }

            if (data.getPostalCountry() == null) {
                return this;
            }
            this.nodes.put(AddressField.COUNTRY, data.getPostalCountry());

            if (data.getAdministrativeArea() == null) {
                return this;
            }
            this.nodes.put(AddressField.ADMIN_AREA, data.getAdministrativeArea());

            if (data.getLocality() == null) {
                return this;
            }
            this.nodes.put(AddressField.LOCALITY, data.getLocality());

            if (data.getDependentLocality() == null) {
                return this;
            }
            this.nodes.put(AddressField.DEPENDENT_LOCALITY, data.getDependentLocality());
            return this;
        }

        LookupKey build() {
            return new LookupKey(this);
        }
    }
}
