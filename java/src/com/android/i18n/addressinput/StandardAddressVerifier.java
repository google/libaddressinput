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

import static com.android.i18n.addressinput.AddressField.ADMIN_AREA;
import static com.android.i18n.addressinput.AddressField.COUNTRY;
import static com.android.i18n.addressinput.AddressField.DEPENDENT_LOCALITY;
import static com.android.i18n.addressinput.AddressField.LOCALITY;
import static com.android.i18n.addressinput.AddressField.ORGANIZATION;
import static com.android.i18n.addressinput.AddressField.POSTAL_CODE;
import static com.android.i18n.addressinput.AddressField.RECIPIENT;
import static com.android.i18n.addressinput.AddressField.SORTING_CODE;
import static com.android.i18n.addressinput.AddressField.STREET_ADDRESS;

import com.android.i18n.addressinput.LookupKey.ScriptType;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

/**
 * Performs various consistency checks on an AddressData. This uses a {@link FieldVerifier} to check
 * each field in the address.
 */
public class StandardAddressVerifier {

    protected final FieldVerifier mRootVerifier;

    protected final VerifierRefiner mRefiner;

    protected final Map<AddressField, List<AddressProblemType>> mProblemMap;

    /**
     * Uses the rootVerifier and {@link #DEFAULT_REFINER} to perform the standard checks on the
     * address fields, as defined in {@link StandardChecks}.
     */
    public StandardAddressVerifier(FieldVerifier rootVerifier) {
        this(rootVerifier, DEFAULT_REFINER, StandardChecks.PROBLEM_MAP);
    }

    /**
     * Uses the rootVerifier and the refiner to perform the standard checks on the address fields,
     * as defined in {@link StandardChecks}.
     */
    public StandardAddressVerifier(FieldVerifier rootVerifier, VerifierRefiner refiner) {
        this(rootVerifier, refiner, StandardChecks.PROBLEM_MAP);
    }

    /**
     * Uses the rootVerifier and {@link #DEFAULT_REFINER} to perform the given checks on the address
     * fields. A reference to problemMap is maintained. It is not modified by this class, and should
     * not be modified subsequent to this call.
     */
    public StandardAddressVerifier(FieldVerifier rootVerifier,
            Map<AddressField, List<AddressProblemType>> problemMap) {
        this(rootVerifier, DEFAULT_REFINER, problemMap);
    }

    /**
     * Uses the rootVerifier and the refiner to perform the given checks on the address fields. A
     * reference to problemMap is maintained. It is not modified by this class, and should not be
     * modified subsequent to this call.
     */
    public StandardAddressVerifier(FieldVerifier rootVerifier, VerifierRefiner refiner,
            Map<AddressField, List<AddressProblemType>> problemMap) {
        mRootVerifier = rootVerifier;
        mRefiner = refiner;
        mProblemMap = StandardChecks.PROBLEM_MAP;
    }

    public void verify(AddressData address, AddressProblems problems) {
        NotifyingListener listener = new NotifyingListener(this);
        verifyAsync(address, problems, listener);
        try {
            listener.waitLoadingEnd();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public void verifyAsync(AddressData address, AddressProblems problems,
            DataLoadListener listener) {
        Thread verifier = new Thread(new Verifier(address, problems, listener));
        verifier.start();
    }

    private class Verifier implements Runnable {
        private AddressData mAddress;
        private AddressProblems mProblems;
        private DataLoadListener mListener;

        Verifier(AddressData address, AddressProblems problems, DataLoadListener listener) {
            mAddress = address;
            mProblems = problems;
            mListener = listener;
        }

        @Override
        public void run() {
            mListener.dataLoadingBegin();

            FieldVerifier v = mRootVerifier;

            ScriptType script = null;
            if (mAddress.getLanguageCode() != null) {
                if (Util.isExplicitLatinScript(mAddress.getLanguageCode())) {
                    script = ScriptType.LATIN;
                } else {
                    script = ScriptType.LOCAL;
                }
            }

            // The first four calls refine the verifier, so must come first, and in this
            // order.
            verifyField(script, v, COUNTRY, mAddress.getPostalCountry(), mProblems);
            if (mProblems.isEmpty()) {
                v = v.refineVerifier(mAddress.getPostalCountry());
                verifyField(script, v, ADMIN_AREA, mAddress.getAdministrativeArea(), mProblems);
                if (mProblems.isEmpty()) {
                    v = v.refineVerifier(mAddress.getAdministrativeArea());
                    verifyField(script, v, LOCALITY, mAddress.getLocality(), mProblems);
                    if (mProblems.isEmpty()) {
                        v = v.refineVerifier(mAddress.getLocality());
                        verifyField(script, v, DEPENDENT_LOCALITY,
                                mAddress.getDependentLocality(), mProblems);
                        if (mProblems.isEmpty()) {
                            v = v.refineVerifier(mAddress.getDependentLocality());
                        }
                    }
                }
            }

            String street = Util.joinAndSkipNulls("\n", mAddress.getAddressLine1(),
                    mAddress.getAddressLine2());

            // remaining calls don't change the field verifier
            verifyField(script, v, POSTAL_CODE, mAddress.getPostalCode(), mProblems);
            verifyField(script, v, STREET_ADDRESS, street, mProblems);
            verifyField(script, v, SORTING_CODE, mAddress.getSortingCode(), mProblems);
            verifyField(script, v, ORGANIZATION, mAddress.getOrganization(), mProblems);
            verifyField(script, v, RECIPIENT, mAddress.getRecipient(), mProblems);

            postVerify(v, mAddress, mProblems);

            mListener.dataLoadingEnd();
        }
    }

    /**
     * Hook to perform any final processing using the final verifier.  Default does no additional
     * verification.
     */
    protected void postVerify(FieldVerifier verifier, AddressData address,
            AddressProblems problems) {
    }

    /**
     * Hook called by verify with each verifiable field, in order.  Override to provide pre- or
     * post-checks for all fields.
     */
    protected boolean verifyField(LookupKey.ScriptType script,
            FieldVerifier verifier, AddressField field, String value,
            AddressProblems problems) {
        Iterator<AddressProblemType> iter = getProblemIterator(field);
        while (iter.hasNext()) {
            AddressProblemType prob = iter.next();
            if (!verifyProblemField(script, verifier, prob, field, value, problems)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Hook for on-the-fly modification of the problem list.  Override to change the problems to
     * check for a particular field.  Generally, changing the problemMap passed to the constructor
     * is a better approach.
     */
    protected Iterator<AddressProblemType> getProblemIterator(AddressField field) {
        List<AddressProblemType> list = mProblemMap.get(field);
        if (list == null) {
            list = Collections.emptyList();
        }
        return list.iterator();
    }

    /**
     * Hook for adding special checks for particular problems and/or fields.
     */
    protected boolean verifyProblemField(LookupKey.ScriptType script,
            FieldVerifier verifier, AddressProblemType problem, AddressField field,
            String datum, AddressProblems problems) {
        return verifier.check(script, problem, field, datum, problems);
    }

    /**
     * This gets called with the hierarchical fields COUNTRY, ADMIN_AREA, LOCALITY,
     * DEPENDENT_LOCALITY in order, returning the refined verifier at each step.
     *
     * <p>The default implementation is stateless, and delegates to the verifier to do the
     * refinement.
     */
    public static class VerifierRefiner {

        /**
         * Refines the verifier.  This delegates to the verifier to perform the refinement.
         */
        public FieldVerifier refineVerifier(FieldVerifier v, AddressField field,
                String subkey) {
            return v.refineVerifier(subkey);
        }

        /**
         * Returns a clean version of the refiner.  Since this implementation is stateless, returns
         * this.
         */
        public VerifierRefiner newInstance() {
            return this;
        }
    }

    private static final VerifierRefiner DEFAULT_REFINER = new VerifierRefiner();
}
