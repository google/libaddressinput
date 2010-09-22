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
    private String id;
    private DataSource dataSource;

    private Set<AddressField> used;
    private Set<AddressField> required;
    // Known values. Can be either a key, a name in Latin, or a name in native script.
    private Map<String, String> known;

    private String[] keys;
    // Names in Latin.
    private String[] lnames;
    // Names in native script.
    private String[] names;

    private Pattern format;
    private Pattern match;

    /**
     * Creates the root field verifier for a particular data source.
     */
    public FieldVerifier(DataSource dataSource) {
        id = "data";
        this.dataSource = dataSource;
        populateRootVerifier();
    }

    /**
     * Creates a field verifier based on its parent and on the new data for this node supplied by
     * nodeData (which may be null).
     */
    private FieldVerifier(FieldVerifier parent, AddressVerificationNodeData nodeData) {
        // Most information is inherited from the parent.
        used = parent.used;
        required = parent.required;
        dataSource = parent.dataSource;
        format = parent.format;
        match = parent.match;
        // Here we add in any overrides from this particular node as well as information such as
        // names, lnames and keys.
        populate(nodeData);
        // known should never be inherited from the parent, but built up from the names in this node.
        known = Util.buildNameToKeyMap(keys, names, lnames);
    }

    /**
     * Sets used, required, keys and known for the root field verifier. This is a little messy at
     * the moment since not all the appropriate information is actually under the root "data" node
     * in the metadata. For example, "used" and "required" are not present there.
     */
    private void populateRootVerifier() {
        // Keys come from the information under "data".
        AddressVerificationNodeData rootNode = dataSource.getDefaultData("data");
        populate(rootNode);
        // "Known" is just the set of keys.
        known = Util.buildNameToKeyMap(keys, null, null);

        // Copy "used" and "required" from the defaults here for bootstrapping. TODO: Investigate
        // putting this information under data itself so this is not needed.
        AddressVerificationNodeData defaultZZ = dataSource.getDefaultData("data/ZZ");
        used = new HashSet<AddressField>();
        if (defaultZZ.containsKey(AddressDataKey.FMT)) {
            used = parseAddressFields(defaultZZ.get(AddressDataKey.FMT));
        }
        required = new HashSet<AddressField>();
        if (defaultZZ.containsKey(AddressDataKey.REQUIRE)) {
            required = parseRequireString(defaultZZ.get(AddressDataKey.REQUIRE));
        }
    }

    private void populate(AddressVerificationNodeData nodeData) {
        if (nodeData == null) {
            return;
        }
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
        if (Util.trimToNull(sublevel) == null) {
            return new FieldVerifier(this, null);
        }
        String subLevelName = id + "/" + sublevel;
        // For names with no latin equivalent, we can look up the sublevel name directly.
        AddressVerificationNodeData nodeData = dataSource.get(subLevelName);
        if (nodeData != null) {
            return new FieldVerifier(this, nodeData);
        }
        // If that failed, then we try to look up the local name equivalent of this latin name.
        // First check these exist.
        if (lnames == null) {
            return new FieldVerifier(this, null);
        }
        for (int n = 0; n < lnames.length; n++) {
            if (lnames[n].equalsIgnoreCase(sublevel)) {
                // We found a match - we should try looking up a key with the local name at the same
                // index.
                subLevelName = id + "/" + names[n];
                nodeData = dataSource.get(subLevelName);
                if (nodeData != null) {
                    return new FieldVerifier(this, nodeData);
                }
            }
        }
        // No sub-verifiers were found.
        return new FieldVerifier(this, null);
    }

    protected boolean check(LookupKey.ScriptType script, AddressProblemType problem,
            AddressField field, String value, AddressProblems problems) {
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
                problemFound = !isKnownInScript(script, trimmedValue);
                break;
            case UNRECOGNIZED_FORMAT:
                if (trimmedValue != null && format != null &&
                        !format.matcher(trimmedValue).matches()) {
                    problemFound = true;
                }
                break;
            case MISMATCHING_VALUE:
                if (trimmedValue != null && match != null &&
                        !match.matcher(trimmedValue).lookingAt()) {
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
        // Country is always required
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
