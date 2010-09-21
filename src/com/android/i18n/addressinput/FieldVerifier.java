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

import java.util.EnumSet;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.regex.Pattern;

/**
 * API to access address verification data used to verify components of an address. Each API
 * implements a different form of verification. <p> Not all fields require all types of validation,
 * although the APIs are designed so that this could be done. In particular, the current
 * implementation only provides known value verification for the hierarchical fields, and only
 * provides format and match verification for the postal code field.
 */
public class FieldVerifier {

    // Assumes root, will be reset to false when initializing with parent.
    private boolean isRoot = true;
    private String id;
    private DataSource data;

    private Set<AddressField> used;
    private Set<AddressField> required;
    // Known values. Can be either a key, a name in Latin, or a name in native script.
    private Map<String, String> known;

    private String[] keys = {};
    // Names in Latin.
    private String[] lnames;
    // Names in native script.
    private String[] names;

    private Pattern format;
    private Pattern match;

    public FieldVerifier(DataSource data) {
        used = new HashSet<AddressField>();
        required = new HashSet<AddressField>();
        id = "data";
        this.data = data;

        AddressVerificationNodeData rootNode = data.getDefaultData("data");
        populate(rootNode);
        known = Util.buildNameToKeyMap(keys, null, null);
    }

    public FieldVerifier(FieldVerifier parent, AddressVerificationNodeData nodeData) {
        isRoot = false;
        used = parent.used;
        required = parent.required;
        data = parent.data;
        format = parent.format;
        match = parent.match;
        known = parent.known;
        populate(nodeData);
        if (known == null) {
            known = new HashMap<String, String>();
        }
        known.putAll(Util.buildNameToKeyMap(keys, names, lnames));
    }

    private void populate(AddressVerificationNodeData nodeData) {
        if (nodeData.containsKey(AddressDataKey.ID)) {
            id = nodeData.get(AddressDataKey.ID);
        }
        if (nodeData.containsKey(AddressDataKey.COUNTRIES)) {
            keys = nodeData.get(AddressDataKey.COUNTRIES).split("~");
        }
        if (nodeData.containsKey(AddressDataKey.XZIP)) {
            format = Pattern.compile(nodeData.get(AddressDataKey.XZIP));
        }
        if (nodeData.containsKey(AddressDataKey.SUB_KEYS)) {
            keys = nodeData.get(AddressDataKey.SUB_KEYS).split("~");
        }
        if (nodeData.containsKey(AddressDataKey.SUB_LNAMES)) {
            lnames = nodeData.get(AddressDataKey.SUB_LNAMES).split("~");
        }
        if (nodeData.containsKey(AddressDataKey.SUB_NAMES)) {
            names = nodeData.get(AddressDataKey.SUB_NAMES).split("~");
        }
        if (nodeData.containsKey(AddressDataKey.FMT)) {
            used = parseAddressFields(nodeData.get(AddressDataKey.FMT));
        }
        if (nodeData.containsKey(AddressDataKey.REQUIRE)) {
            required = parseRequireString(nodeData.get(AddressDataKey.REQUIRE));
        }
        if (nodeData.containsKey(AddressDataKey.ZIP)) {
            if (isCountryKey()) {
                format = Pattern.compile(nodeData.get(AddressDataKey.ZIP));
            } else {
                match = Pattern.compile(nodeData.get(AddressDataKey.ZIP));
            }
        }
        if (keys != null && names == null && lnames != null && keys.length == lnames.length) {
            names = keys;
        }
    }

    FieldVerifier refineVerifier(String sublevel) {
        String subLevelName = id + "/" + sublevel;
        AddressVerificationNodeData nodeData = data.get(subLevelName);
        if (nodeData == null) {
            if (lnames != null) {
                int n = 0;
                boolean found = false;
                while (n < lnames.length) {
                    if (lnames[n].equalsIgnoreCase(sublevel)) {
                        found = true;
                        break;
                    }
                    n++;
                }
                if (!found) {
                    return this;
                }
                subLevelName = id + "/" + names[n];
                nodeData = data.get(subLevelName);
                if (nodeData == null) {
                    return this;
                } else {
                    return new FieldVerifier(this, nodeData);
                }
            }
            return this;
        }
        return new FieldVerifier(this, nodeData);
    }

    private void report(AddressProblemType problem, AddressField field, String value,
            AddressProblems problems) {
        problems.add(field, problem);
    }

    protected boolean check(LookupKey.ScriptType script, AddressProblemType problem,
            AddressField field, String value, AddressProblems problems) {
        // Assumes no problem found
        boolean problemFound = false;

        String trimmedValue = Util.trimToNull(value);
        switch (problem) {
            case UNUSED_FIELD:
                if (trimmedValue != null && !used.contains(field)) {
                    problemFound = true;
                }
                break;
            case MISSING_REQUIRED_FIELD:
                if (required.contains(field) && trimmedValue == null) {
                    problemFound = true;
                }
                break;
            case UNKNOWN_VALUE:
                // An empty string will never be an UNKNOWN_VALUE. It is invalid
                // only when it appears in a required field (In that case it will
                // be reported as MISSING_REQUIRED_FIELD).
                if (trimmedValue == null) {
                    break;
                }
                // Hack will be fixed later
                // problemFound = !isKnownInScript(script, value);
                break;
            case UNRECOGNIZED_FORMAT:
                if (trimmedValue != null && format != null &&
                        !format.matcher(value == null ? "" : value).matches()) {
                    problemFound = true;
                }
                break;
            case MISMATCHING_VALUE:
                if (trimmedValue != null && match != null &&
                        !match.matcher(value == null ? "" : value).lookingAt()) {
                    problemFound = true;
                }
                break;
            default:
                throw new RuntimeException("unknown problem: " + problem);
        }
        if (problemFound) {
            problems.add(field, problem);
        }
        return !problemFound;
    }

    private boolean isKnownInScript(LookupKey.ScriptType script, String value) {
        String trimmedValue = Util.trimToNull(value);
        Util.checkNotNull(trimmedValue);
        if (script == null) {
            return known == null || known.containsKey(trimmedValue.toLowerCase());
        }
        String[] currNames =
                script == LookupKey.ScriptType.LATIN ? lnames : names;
        Set<String> candidates = new HashSet<String>();
        if (currNames != null) {
            for (String name : currNames) {
                candidates.add(name.toLowerCase());
            }
        }
        if (keys != null) {
            for (String name : keys) {
                candidates.add(name.toLowerCase());
            }
        }

        if (candidates.size() == 0 || trimmedValue == null) {
            return true;
        }

        return candidates.contains(value.toLowerCase());
    }

    public String toString() {
        return id;
    }

    // Util methods for parsing node content.
    private static Set<AddressField> parseAddressFields(String value) {
        EnumSet<AddressField> result = EnumSet.of(AddressField.COUNTRY);
        boolean escaped = false;
        for (char c : value.toCharArray()) {
            if (escaped) {
                escaped = false;
                if (c == 'n') {
                    continue;
                }
                AddressField f = AddressField.of(c);
                if (f == null) {
                    throw new RuntimeException(
                            "Unrecognized character '" + c + "' in format pattern: "
                                    + value);
                }
                result.add(f);
            } else if (c == '%') {
                escaped = true;
            }
        }
        // TODO: Investigate this.
        // For some reason Address 1 & 2 is removed if they are specified as fields.
        // I assume this is due to errors in data, but I don't know.
        result.remove(AddressField.ADDRESS_LINE_1);
        result.remove(AddressField.ADDRESS_LINE_2);

        return result;
    }

    private static Set<AddressField> parseRequireString(String value) {
        // country is always required
        EnumSet<AddressField> result = EnumSet.of(AddressField.COUNTRY);

        for (char c : value.toCharArray()) {
            AddressField f = AddressField.of(c);
            if (f == null) {
                throw new RuntimeException("Unrecognized character '" + c + "' in require pattern: "
                        + value);
            }
            result.add(f);
        }

        // TODO: Investigate this.
        // For some reason Address 1 & 2 is removed if they are specified as required.
        // I assume this is due to errors in data, but I don't know.
        result.remove(AddressField.ADDRESS_LINE_1);
        result.remove(AddressField.ADDRESS_LINE_2);

        return result;
    }

    private boolean isCountryKey() {
        Util.checkNotNull(id, "cannot use null as key");
        return id.split("/").length == 2;
    }
}
