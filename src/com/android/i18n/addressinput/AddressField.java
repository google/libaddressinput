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

import java.util.HashMap;
import java.util.Map;

/**
 * Defines the character codes used in the metadata to specify the types of fields used in address
 * formatting. Note that the metadata also has a character for newlines, which is not defined
 * here.
 * @author Lara Rennie
 */
public enum AddressField {
  ADMIN_AREA('S', "state"),
  LOCALITY('C', "city"),
  RECIPIENT('N', "name"),
  ORGANIZATION('O', "organization"),
  ADDRESS_LINE_1('1', "street1"),
  ADDRESS_LINE_2('2', "street2"),
  DEPENDENT_LOCALITY('D'),
  POSTAL_CODE('Z'),
  SORTING_CODE('X'),

  // TODO: Remove STREET_ADDRESS and use ADDRESS_LINE_1 and ADDRESS_LINE_2
  // instead. This will involve updating the metadata to specify '1' and '2' instead
  // of 'A'.
  // Deprecated.
  STREET_ADDRESS('A'),

  COUNTRY('R');

  private static Map<Character, AddressField> fieldMapping = new HashMap<Character, AddressField>();

  static {
    for (AddressField val : values()) {
      fieldMapping.put(val.getChar(), val);
    }
  }

  private final char field;
  private final String attributeName;

  private AddressField(char field, String attributeName) {
    this.field = field;
    this.attributeName = attributeName;
  }

  private AddressField(char field) {
    this(field, null);
  }

  /**
   * Gets the corresponding AddressField for the character code.
   * Returns null if the character is not recognized.
   */
  public static AddressField of(char field) {
    return fieldMapping.get(field);
  }

  /**
   * Gets attribute name. Attribute names are used as keys to JSON address data
   * returned from the server. Returns null if the field does not have a
   * corresponding attribute name.
   *
   * Note: Not all address fields have attribute names. Fields like postal
   * code, country, sorting code, or street address do not have attribute names.
   */
  public String getAttributeName() {
    return attributeName;
  }

  /**
   * Gets the field's identification character, as used in the metadata.
   * @return identification char.
   */
  public char getChar() {
    return field;
  }
}
