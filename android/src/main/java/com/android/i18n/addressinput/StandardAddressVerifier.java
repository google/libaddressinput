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
public final class StandardAddressVerifier {

  private static final String LOCALE_DELIMITER = "--";

  protected final FieldVerifier rootVerifier;

  protected final Map<AddressField, List<AddressProblemType>> problemMap;

  /**
   * Uses the rootVerifier to perform the standard checks on the address fields, as defined in
   * {@link StandardChecks}.
   */
  public StandardAddressVerifier(FieldVerifier rootVerifier) {
    this(rootVerifier, StandardChecks.PROBLEM_MAP);
  }

  /**
   * Uses the rootVerifier to perform the given checks on the address fields. A reference to
   * problemMap is maintained. It is not modified by this class, and should not be modified
   * subsequent to this call.
   */
  public StandardAddressVerifier(FieldVerifier rootVerifier,
      Map<AddressField, List<AddressProblemType>> problemMap) {
    this.rootVerifier = rootVerifier;
    this.problemMap = problemMap;
  }

  /**
   * Verifies the address, reporting problems to problems.
   */
  public void verify(AddressData address, AddressProblems problems) {
    NotifyingListener listener = new NotifyingListener();
    verifyAsync(address, problems, listener);
    try {
      listener.waitLoadingEnd();
    } catch (InterruptedException e) {
      throw new RuntimeException(e);
    }
  }

  public void verifyAsync(
      AddressData address, AddressProblems problems, DataLoadListener listener) {
    Thread verifier = new Thread(new Verifier(address, problems, listener));
    verifier.start();
  }

  private class Verifier implements Runnable {
    private AddressData address;
    private AddressProblems problems;
    private DataLoadListener listener;

    Verifier(AddressData address, AddressProblems problems, DataLoadListener listener) {
      this.address = address;
      this.problems = problems;
      this.listener = listener;
    }

    @Override
    public void run() {
      listener.dataLoadingBegin();

      FieldVerifier v = rootVerifier;

      ScriptType script = null;
      if (address.getLanguageCode() != null) {
        if (Util.isExplicitLatinScript(address.getLanguageCode())) {
          script = ScriptType.LATIN;
        } else {
          script = ScriptType.LOCAL;
        }
      }

      // The first four calls refine the verifier, so must come first, and in this
      // order.
      verifyField(script, v, COUNTRY, address.getPostalCountry(), problems);
      if (problems.isEmpty()) {
        // Ensure we start with the right language country sub-key.
        String countrySubKey = address.getPostalCountry();
        if (address.getLanguageCode() != null && !address.getLanguageCode().equals("")) {
          countrySubKey += (LOCALE_DELIMITER + address.getLanguageCode());
        }
        v = v.refineVerifier(countrySubKey);
        verifyField(script, v, ADMIN_AREA, address.getAdministrativeArea(), problems);
        if (problems.isEmpty()) {
          v = v.refineVerifier(address.getAdministrativeArea());
          verifyField(script, v, LOCALITY, address.getLocality(), problems);
          if (problems.isEmpty()) {
            v = v.refineVerifier(address.getLocality());
            verifyField(script, v, DEPENDENT_LOCALITY, address.getDependentLocality(), problems);
            if (problems.isEmpty()) {
              v = v.refineVerifier(address.getDependentLocality());
            }
          }
        }
      }

    // This concatenation is for the purpose of validation only - the important part is to check we
    // have at least one value filled in for lower-level components.
      String street =
          Util.joinAndSkipNulls("\n", address.getAddressLine1(),
              address.getAddressLine2());

      // Remaining calls don't change the field verifier.
      verifyField(script, v, POSTAL_CODE, address.getPostalCode(), problems);
      verifyField(script, v, STREET_ADDRESS, street, problems);
      verifyField(script, v, SORTING_CODE, address.getSortingCode(), problems);
      verifyField(script, v, ORGANIZATION, address.getOrganization(), problems);
      verifyField(script, v, RECIPIENT, address.getRecipient(), problems);

      postVerify(v, address, problems);

      listener.dataLoadingEnd();
    }
  }

  /**
   * Hook to perform any final processing using the final verifier.  Default does no additional
   * verification.
   */
  protected void postVerify(FieldVerifier verifier, AddressData address, AddressProblems problems) {
  }

  /**
   * Hook called by verify with each verifiable field, in order.  Override to provide pre- or
   * post-checks for all fields.
   */
  protected boolean verifyField(LookupKey.ScriptType script, FieldVerifier verifier,
      AddressField field, String value, AddressProblems problems) {
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
    List<AddressProblemType> list = problemMap.get(field);
    if (list == null) {
      list = Collections.emptyList();
    }
    return list.iterator();
  }

  /**
   * Hook for adding special checks for particular problems and/or fields.
   */
  protected boolean verifyProblemField(LookupKey.ScriptType script, FieldVerifier verifier,
      AddressProblemType problem, AddressField field, String datum, AddressProblems problems) {
    return verifier.check(script, problem, field, datum, problems);
  }
}
