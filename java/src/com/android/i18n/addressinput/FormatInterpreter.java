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

import com.android.i18n.addressinput.LookupKey.ScriptType;

import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONTokener;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Address format interpreter. A utility to find address format related info.
 */
class FormatInterpreter {

    private static final String NEW_LINE = "%n";

    private final String mDefaultFormat;

    private final FormOptions mFormOptions;

    /**
     * Creates a new instance of {@link FormatInterpreter}.
     */
    FormatInterpreter(FormOptions options) {
        Util.checkNotNull(RegionDataConstants.getCountryFormatMap(),
                "null country name map not allowed");
        Util.checkNotNull(options);
        mFormOptions = options;
        mDefaultFormat = getJsonValue("ZZ", AddressDataKey.FMT);
        Util.checkNotNull(mDefaultFormat, "null default format not allowed");
    }

    /**
     * Returns a list of address fields based on the format of {@code regionCode}. Script type is
     * needed because some countries uses different address formats for local/Latin scripts.
     *
     * @param scriptType if {@link ScriptType#LOCAL}, use local format; else use Latin format.
     */
    List<AddressField> getAddressFieldOrder(ScriptType scriptType, String regionCode) {
        Util.checkNotNull(scriptType);
        Util.checkNotNull(regionCode);
        List<AddressField> fieldOrder = new ArrayList<AddressField>();
        for (String substring : getFormatSubStrings(scriptType, regionCode)) {
            // Skips un-escaped characters and new lines.
            if (!substring.matches("%.") || substring.equals(NEW_LINE)) {
                continue;
            }

            AddressField field = AddressField.of(substring.charAt(1));
            fieldOrder.add(field);
        }

        overrideFieldOrder(regionCode, fieldOrder);

        // Uses two address lines instead of street address.
        List<AddressField> finalFieldOrder = new ArrayList<AddressField>();
        for (AddressField field : fieldOrder) {
            if (field == AddressField.STREET_ADDRESS) {
                finalFieldOrder.add(AddressField.ADDRESS_LINE_1);
                finalFieldOrder.add(AddressField.ADDRESS_LINE_2);
            } else {
                finalFieldOrder.add(field);
            }
        }
        return finalFieldOrder;
    }

    /**
     * Returns a list of address fields based on the format of {@code regionCode} -- assuming script
     * type is {@link ScriptType#LOCAL}.
     */
    List<AddressField> getAddressFieldOrder(String regionCode) {
        Util.checkNotNull(regionCode);
        return getAddressFieldOrder(ScriptType.LOCAL, regionCode);
    }

    private void overrideFieldOrder(String regionCode, List<AddressField> fieldOrder) {
        if (mFormOptions.getCustomFieldOrder(regionCode) == null) {
            return;
        }

        // Constructs a hash for overridden field order.
        final Map<AddressField, Integer> fieldPriority = new HashMap<AddressField, Integer>();
        int i = 0;
        for (AddressField field : mFormOptions.getCustomFieldOrder(regionCode)) {
            fieldPriority.put(field, i);
            i++;
        }

        // Finds union of input fields and priority list.
        List<AddressField> union = new ArrayList<AddressField>();
        List<Integer> slots = new ArrayList<Integer>();
        i = 0;
        for (AddressField field : fieldOrder) {
            if (fieldPriority.containsKey(field)) {
                union.add(field);
                slots.add(i);
            }
            i++;
        }

        // Overrides field order with priority list.
        Collections.sort(union, new Comparator<AddressField>() {
            @Override
            public int compare(AddressField o1, AddressField o2) {
                return fieldPriority.get(o1) - fieldPriority.get(o2);
            }
        });

        // Puts reordered fields in slots.
        for (int j = 0; j < union.size(); ++j) {
            fieldOrder.set(slots.get(j), union.get(j));
        }
    }

    /**
     * Gets formatted address. For example,
     *
     * <p> John Doe<br> Dnar Corp<br> 5th St<br> Santa Monica CA 90123 </p>
     *
     * This method does not validate addresses. Also, it will "normalize" the result strings by
     * removing redundant spaces and empty lines.
     */
    List<String> getEnvelopeAddress(AddressData address) {
        Util.checkNotNull(address, "null input address not allowed");
        String regionCode = address.getPostalCountry();

        String lc = address.getLanguageCode();
        ScriptType scriptType = ScriptType.LOCAL;
        if (lc != null) {
            scriptType = Util.isExplicitLatinScript(lc) ? ScriptType.LATIN : ScriptType.LOCAL;
        }

        List<String> lines = new ArrayList<String>();
        StringBuilder currentLine = new StringBuilder();
        for (String formatSymbol : getFormatSubStrings(scriptType, regionCode)) {
            if (formatSymbol.equals(NEW_LINE)) {
                String normalizedStr =
                        removeRedundantSpacesAndLeadingPunctuation(currentLine.toString());
                if (normalizedStr.length() > 0) {
                    lines.add(normalizedStr);
                    currentLine.setLength(0);
                }
            } else if (formatSymbol.startsWith("%")) {
                char c = formatSymbol.charAt(1);
                AddressField field = AddressField.of(c);
                Util.checkNotNull(field, "null address field for character " + c);

                String value = null;
                switch (field) {
                    case STREET_ADDRESS:
                        value = Util.joinAndSkipNulls("\n",
                                address.getAddressLine1(),
                                address.getAddressLine2());
                        break;
                    case COUNTRY:
                        // Country name is treated separately.
                        break;
                    case ADMIN_AREA:
                        value = address.getAdministrativeArea();
                        break;
                    case LOCALITY:
                        value = address.getLocality();
                        break;
                    case DEPENDENT_LOCALITY:
                        value = address.getDependentLocality();
                        break;
                    case RECIPIENT:
                        value = address.getRecipient();
                        break;
                    case ORGANIZATION:
                        value = address.getOrganization();
                        break;
                    case POSTAL_CODE:
                        value = address.getPostalCode();
                        break;
                    default:
                        break;
                }

                if (value != null) {
                    currentLine.append(value);
                }
            } else {
                currentLine.append(formatSymbol);
            }
        }
        String normalizedStr = removeRedundantSpacesAndLeadingPunctuation(currentLine.toString());
        if (normalizedStr.length() > 0) {
            lines.add(normalizedStr);
        }
        return lines;
    }

    /**
     * Tokenizes the format string and returns the token string list. "%" is treated as an escape
     * character. So for example "%n%a%nxyz" will be split into "%n", "%a", "%n", "x", "y", and "z".
     * Escaped tokens correspond to either new line or address fields.
     */
    private List<String> getFormatSubStrings(ScriptType scriptType, String regionCode) {
        String formatString = getFormatString(scriptType, regionCode);
        List<String> parts = new ArrayList<String>();

        boolean escaped = false;
        for (char c : formatString.toCharArray()) {
            if (escaped) {
                escaped = false;
                if (NEW_LINE.equals("%" + c)) {
                    parts.add(NEW_LINE);
                } else {
                    Util.checkNotNull(AddressField.of(c), "Unrecognized character '" + c
                            + "' in format pattern: " + formatString);
                    parts.add("%" + c);
                }
            } else if (c == '%') {
                escaped = true;
            } else {
                parts.add(c + "");
            }
        }
        return parts;
    }

    private static String removeRedundantSpacesAndLeadingPunctuation(String str) {
        // Remove leading commas and other punctuation that might have been added by the formatter
        // in the case of missing data.
        str = str.replaceFirst("^[-,\\s]+", "");
        str = str.trim();
        str = str.replaceAll(" +", " ");
        return str;
    }

    private static String getFormatString(ScriptType scriptType, String regionCode) {
        String format = (scriptType == ScriptType.LOCAL)
                ? getJsonValue(regionCode, AddressDataKey.FMT)
                : getJsonValue(regionCode, AddressDataKey.LFMT);
        if (format == null) {
            format = getJsonValue("ZZ", AddressDataKey.FMT);
        }
        return format;
    }

    private static String getJsonValue(String regionCode, AddressDataKey key) {
        Util.checkNotNull(regionCode);
        String jsonString = RegionDataConstants.getCountryFormatMap().get(regionCode);
        Util.checkNotNull(jsonString, "no json data for region code " + regionCode);

        try {
            JSONObject jsonObj = new JSONObject(new JSONTokener(jsonString));
            if (!jsonObj.has(key.name().toLowerCase())) {
                // Key not found. Return null.
                return null;
            }
            // Gets the string for this key.
            String parsedJsonString = jsonObj.getString(key.name().toLowerCase());
            return parsedJsonString;
        } catch (JSONException e) {
            throw new RuntimeException("Invalid json for region code " + regionCode
                    + ": " + jsonString);
        }
    }
}
