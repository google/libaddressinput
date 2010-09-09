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

package com.android.i18n.addressinput.validation;

import com.android.i18n.addressinput.AddressField;

import java.util.HashMap;
import java.util.Map;

/**
 * This structure keeps track of any errors found when validating the AddressData.
 */
public class AddressProblems {
  private Map<AddressField, AddressProblemType> problems;

  public AddressProblems() {
    problems = new HashMap<AddressField, AddressProblemType>();
  } 

 /**
  * Only one address problem is saved per addressField. Address field as used here refers to the
  * different data parts in the AddressData class. 
  */
  public void add(AddressField addressField, AddressProblemType problem) {
    problems.put(addressField, problem);
  }

  /**
   * Returns true if no problems have been added.
   */
  public boolean isEmpty() {
    return problems.isEmpty();
  }

  public String toString() {
    return problems.toString();
  }

  /**
   * Returns null if no problem exists.  
   */
  public AddressProblemType getProblem(AddressField addressField) {
    return problems.get(addressField);
  }

  /**
   * This will return an empty map if there are no problems.
   */
  public Map<AddressField, AddressProblemType> getProblems() {
    return problems;
  }
}
