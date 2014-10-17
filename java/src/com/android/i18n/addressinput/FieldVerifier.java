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
import java.util.List;
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

    private static final FormatInterpreter FORMAT_INTERPRETER =
        new FormatInterpreter(new FormOptions.Builder().build());

    // Package-private so it can be accessed by tests.
    String mId;
    private DataSource mDataSource;

    // Package-private so they can be accessed by tests.
    Set<AddressField> mPossiblyUsedFields;
    Set<AddressField> mRequired;
    // Known values. Can be either a key, a name in Latin, or a name in native script.
    private Map<String, String> mCandidateValues;

    // Keys for the subnodes of this verifier. For example, a key for the US would be CA, since
    // there is a sub-verifier with the ID "data/US/CA". Keys may be the local names of the
    // locations in the next level of the hierarchy, or the abbreviations if suitable abbreviations
    // exist. Package-private so it can be accessed by tests.
    String[] mKeys;
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
     *
     * Package-private so it can be accessed by tests.
     */
    FieldVerifier(FieldVerifier parent, AddressVerificationNodeData nodeData) {
        // Most information is inherited from the parent.
        mPossiblyUsedFields = parent.mPossiblyUsedFields;
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
     * Sets possiblyUsedFields, required, keys and candidateValues for the root field verifier.
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

        // TODO: Investigate if these need to be set here. The country level population already
        // handles the fallback, the question is if validation can be done without a country level
        // validator being created.
        // Copy "possiblyUsedFields" and "required" from the defaults here for bootstrapping.
        mPossiblyUsedFields = new HashSet<AddressField>();
        mRequired = new HashSet<AddressField>();
        populatePossibleAndRequired("ZZ");
    }

    /**
     * Populates this verifier with data from the node data passed in and from RegionDataConstants.
     * The node data may be null.
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

        // These fields are populated from RegionDataConstants so that the metadata server can be
        // updated without needing to be in sync with clients.
        if (isCountryKey()) {
            populatePossibleAndRequired(mId.split(KEY_DELIMITER)[1]);
        }
    }

    private void populatePossibleAndRequired(String regionCode) {
        List<AddressField> possible = FORMAT_INTERPRETER.getAddressFieldOrder(regionCode);
        mPossiblyUsedFields = convertAddressFieldsToPossiblyUsedSet(possible);
        mRequired = FormatInterpreter.getRequiredFields(regionCode);
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
                if (trimmedValue != null && !mPossiblyUsedFields.contains(field)) {
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
     * Converts a list of address fields to a set of possibly used fields. Adds country and handles
     * street address.
     */
    private static Set<AddressField> convertAddressFieldsToPossiblyUsedSet(
            List<AddressField> fields) {
        // COUNTRY is never unexpected.
        EnumSet<AddressField> result = EnumSet.of(AddressField.COUNTRY);
        for (AddressField field : fields) {
            // Replace ADDRESS_LINE with STREET_ADDRESS because that's what the validation expects.
            if (field == AddressField.ADDRESS_LINE_1 ||
                field == AddressField.ADDRESS_LINE_2) {
                result.add(AddressField.STREET_ADDRESS);
            } else {
                result.add(field);
            }
        }
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
