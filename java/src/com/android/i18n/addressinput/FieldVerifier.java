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

import java.util.EnumSet;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.regex.Pattern;

/**
 * Accesses address verification data used to verify components of an address.
 * <p> Not all fields require all types of validation, although this could be done. In particular,
 * the current implementation only provides known value verification for the hierarchical fields,
 * and only provides format and match verification for the postal code field.
 */
public class FieldVerifier {
    // Node data values are delimited by this symbol.
    private static final String DATA_DELIMITER = "~";
    // Keys are built up using this delimiter: eg data/US, data/US/CA.
    private static final String KEY_DELIMITER = "/";

    private String mId;
    private DataSource mDataSource;

    private Set<AddressField> mPossibleFields;
    private Set<AddressField> mRequired;
    // Known values. Can be either a key, a name in Latin, or a name in native script.
    private Map<String, String> mCandidateValues;

    // Keys for the subnodes of this verifier. For example, a key for the US would be CA, since
    // there is a sub-verifier with the ID "data/US/CA". Keys may be the local names of the
    // locations in the next level of the hierarchy, or the abbreviations if suitable abbreviations
    // exist.
    private String[] mKeys;
    // Names in Latin. These are only populated if the native/local names are in a script other than
    // latin.
    private String[] mLatinNames;
    // Names in native script.
    private String[] mLocalNames;

    // Pattern representing the format of a postal code number.
    private Pattern mFormat;
    // Defines the valid range of a postal code number.
    private Pattern mMatch;

    /**
     * Creates the root field verifier for a particular data source.
     */
    public FieldVerifier(DataSource dataSource) {
        mDataSource = dataSource;
        populateRootVerifier();
    }

    /**
     * Creates a field verifier based on its parent and on the new data for this node supplied by
     * nodeData (which may be null).
     */
    private FieldVerifier(FieldVerifier parent, AddressVerificationNodeData nodeData) {
        // Most information is inherited from the parent.
        mPossibleFields = parent.mPossibleFields;
        mRequired = parent.mRequired;
        mDataSource = parent.mDataSource;
        mFormat = parent.mFormat;
        mMatch = parent.mMatch;
        // Here we add in any overrides from this particular node as well as information such as
        // localNames, latinNames and keys.
        populate(nodeData);
        // candidateValues should never be inherited from the parent, but built up from the
        // localNames in this node.
        mCandidateValues = Util.buildNameToKeyMap(mKeys, mLocalNames, mLatinNames);
    }

    /**
     * Sets possibleFieldsUsed, required, keys and candidateValues for the root field verifier. This
     * is a little messy at the moment since not all the appropriate information is actually under
     * the root "data" node in the metadata. For example, "possibleFields" and "required" are not
     * present there.
     */
    private void populateRootVerifier() {
        mId = "data";
        // Keys come from the countries under "data".
        AddressVerificationNodeData rootNode = mDataSource.getDefaultData("data");
        if (rootNode.containsKey(AddressDataKey.COUNTRIES)) {
            mKeys = rootNode.get(AddressDataKey.COUNTRIES).split(DATA_DELIMITER);
        }
        // candidateValues is just the set of keys.
        mCandidateValues = Util.buildNameToKeyMap(mKeys, null, null);

        // Copy "possibleFieldsUsed" and "required" from the defaults here for bootstrapping.
        // TODO: Investigate a cleaner way of doing this - maybe we should populate "data" with this
        // information instead.
        AddressVerificationNodeData defaultZZ = mDataSource.getDefaultData("data/ZZ");
        mPossibleFields = new HashSet<AddressField>();
        if (defaultZZ.containsKey(AddressDataKey.FMT)) {
            mPossibleFields = parseAddressFields(defaultZZ.get(AddressDataKey.FMT));
        }
        mRequired = new HashSet<AddressField>();
        if (defaultZZ.containsKey(AddressDataKey.REQUIRE)) {
            mRequired = parseRequireString(defaultZZ.get(AddressDataKey.REQUIRE));
        }
    }

    /**
     * Populates this verifier with data from the node data passed in. This may be null.
     */
    private void populate(AddressVerificationNodeData nodeData) {
        if (nodeData == null) {
            return;
        }
        if (nodeData.containsKey(AddressDataKey.ID)) {
            mId = nodeData.get(AddressDataKey.ID);
        }
        if (nodeData.containsKey(AddressDataKey.SUB_KEYS)) {
            mKeys = nodeData.get(AddressDataKey.SUB_KEYS).split(DATA_DELIMITER);
        }
        if (nodeData.containsKey(AddressDataKey.SUB_LNAMES)) {
            mLatinNames = nodeData.get(AddressDataKey.SUB_LNAMES).split(DATA_DELIMITER);
        }
        if (nodeData.containsKey(AddressDataKey.SUB_NAMES)) {
            mLocalNames = nodeData.get(AddressDataKey.SUB_NAMES).split(DATA_DELIMITER);
        }
        if (nodeData.containsKey(AddressDataKey.FMT)) {
            mPossibleFields = parseAddressFields(nodeData.get(AddressDataKey.FMT));
        }
        if (nodeData.containsKey(AddressDataKey.REQUIRE)) {
            mRequired = parseRequireString(nodeData.get(AddressDataKey.REQUIRE));
        }
        if (nodeData.containsKey(AddressDataKey.XZIP)) {
            mFormat = Pattern.compile(nodeData.get(AddressDataKey.XZIP), Pattern.CASE_INSENSITIVE);
        }
        if (nodeData.containsKey(AddressDataKey.ZIP)) {
            // This key has two different meanings, depending on whether this is a country-level key
            // or not.
            if (isCountryKey()) {
                mFormat = Pattern.compile(nodeData.get(AddressDataKey.ZIP),
                                          Pattern.CASE_INSENSITIVE);
            } else {
                mMatch = Pattern.compile(nodeData.get(AddressDataKey.ZIP),
                                         Pattern.CASE_INSENSITIVE);
            }
        }
        // If there are latin names but no local names, and there are the same number of latin names
        // as there are keys, then we assume the local names are the same as the keys.
        if (mKeys != null && mLocalNames == null && mLatinNames != null &&
            mKeys.length == mLatinNames.length) {
            mLocalNames = mKeys;
        }
    }

    FieldVerifier refineVerifier(String sublevel) {
        if (Util.trimToNull(sublevel) == null) {
            return new FieldVerifier(this, null);
        }
        // If the parent node didn't exist, then the subLevelName will start with "null".
        String subLevelName = mId + KEY_DELIMITER + sublevel;
        // For names with no Latin equivalent, we can look up the sublevel name directly.
        AddressVerificationNodeData nodeData = mDataSource.get(subLevelName);
        if (nodeData != null) {
            return new FieldVerifier(this, nodeData);
        }
        // If that failed, then we try to look up the local name equivalent of this latin name.
        // First check these exist.
        if (mLatinNames == null) {
            return new FieldVerifier(this, null);
        }
        for (int n = 0; n < mLatinNames.length; n++) {
            if (mLatinNames[n].equalsIgnoreCase(sublevel)) {
                // We found a match - we should try looking up a key with the local name at the same
                // index.
                subLevelName = mId + KEY_DELIMITER + mLocalNames[n];
                nodeData = mDataSource.get(subLevelName);
                if (nodeData != null) {
                    return new FieldVerifier(this, nodeData);
                }
            }
        }
        // No sub-verifiers were found.
        return new FieldVerifier(this, null);
    }

    /**
     * Returns the ID of this verifier.
     */
    @Override
    public String toString() {
        return mId;
    }

    /**
     * Checks a value in a particular script for a particular field to see if it causes the problem
     * specified. If so, this problem is added to the AddressProblems collection passed in. Returns
     * true if no problem was found.
     */
    protected boolean check(ScriptType script, AddressProblemType problem, AddressField field,
            String value, AddressProblems problems) {
        boolean problemFound = false;

        String trimmedValue = Util.trimToNull(value);
        switch (problem) {
            case USING_UNUSED_FIELD:
                if (trimmedValue != null && !mPossibleFields.contains(field)) {
                    problemFound = true;
                }
                break;
            case MISSING_REQUIRED_FIELD:
                if (mRequired.contains(field) && trimmedValue == null) {
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
                if (trimmedValue != null && mFormat != null &&
                        !mFormat.matcher(trimmedValue).matches()) {
                    problemFound = true;
                }
                break;
            case MISMATCHING_VALUE:
                if (trimmedValue != null && mMatch != null &&
                        !mMatch.matcher(trimmedValue).lookingAt()) {
                    problemFound = true;
                }
                break;
            default:
                throw new RuntimeException("Unknown problem: " + problem);
        }
        if (problemFound) {
            problems.add(field, problem);
        }
        return !problemFound;
    }

    /**
     * Checks the value of a particular field in a particular script against the known values for
     * this field. If script is null, it checks both the local and the latin values. Otherwise it
     * checks only the values in the script specified.
     */
    private boolean isKnownInScript(ScriptType script, String value) {
        String trimmedValue = Util.trimToNull(value);
        Util.checkNotNull(trimmedValue);
        if (script == null) {
            return (mCandidateValues == null ||
                    mCandidateValues.containsKey(trimmedValue.toLowerCase()));
        }
        // Otherwise, if we know the script, we want to restrict the candidates to only names in
        // that script.
        String[] namesToConsider = (script == ScriptType.LATIN) ? mLatinNames : mLocalNames;
        Set<String> candidates = new HashSet<String>();
        if (namesToConsider != null) {
            for (String name : namesToConsider) {
                candidates.add(name.toLowerCase());
            }
        }
        if (mKeys != null) {
            for (String name : mKeys) {
                candidates.add(name.toLowerCase());
            }
        }

        if (candidates.size() == 0 || trimmedValue == null) {
            return true;
        }

        return candidates.contains(value.toLowerCase());
    }

    /**
     * Parses the value of the "fmt" key in the data to see which fields are used for a particular
     * country. Returns a list of all fields found. Country is always assumed to be present. Skips
     * characters that indicate new-lines in the format information, as well as any characters not
     * escaped with "%".
     */
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
                            "Unrecognized character '" + c + "' in format pattern: " + value);
                }
                result.add(f);
            } else if (c == '%') {
                escaped = true;
            }
        }
        // These fields are not mentioned in the metadata at the moment since there is an effort to
        // move away from STREET_ADDRESS and use these fields instead. This means they have to be
        // removed here.
        result.remove(AddressField.ADDRESS_LINE_1);
        result.remove(AddressField.ADDRESS_LINE_2);

        return result;
    }

    /**
     * Parses the value of the "required" key in the data. Adds country as well as any other field
     * mentioned in the string.
     */
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
        // These fields are not mentioned in the metadata at the moment since there is an effort to
        // move away from STREET_ADDRESS and use these fields instead. This means they have to be
        // removed here.
        result.remove(AddressField.ADDRESS_LINE_1);
        result.remove(AddressField.ADDRESS_LINE_2);

        return result;
    }

    /**
     * Returns true if this key represents a country. We assume all keys with only one delimiter are
     * at the country level (such as "data/US").
     */
    private boolean isCountryKey() {
        Util.checkNotNull(mId, "Cannot use null as key");
        return mId.split(KEY_DELIMITER).length == 2;
    }
}
