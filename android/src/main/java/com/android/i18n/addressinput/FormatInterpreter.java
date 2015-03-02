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
import java.util.EnumSet;
import java.util.List;
import java.util.Set;

/**
 * Address format interpreter. A utility to find address format related info.
 */
final class FormatInterpreter {

  private static final String NEW_LINE = "%n";

  private final FormOptions formOptions;

  /**
   * Creates a new instance of {@link FormatInterpreter}.
   */
  FormatInterpreter(FormOptions options) {
    Util.checkNotNull(
        RegionDataConstants.getCountryFormatMap(), "null country name map not allowed");
    Util.checkNotNull(options);
    this.formOptions = options;
    Util.checkNotNull(getJsonValue("ZZ", AddressDataKey.FMT),
        "Could not obtain a default address field order.");
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
    EnumSet<AddressField> visibleFields = EnumSet.noneOf(AddressField.class);
    List<AddressField> fieldOrder = new ArrayList<AddressField>();
    // TODO: Change this to just enumerate the address fields directly.
    for (String substring : getFormatSubStrings(scriptType, regionCode)) {
      // Skips un-escaped characters and new lines.
      if (!substring.matches("%.") || substring.equals(NEW_LINE)) {
        continue;
      }
      AddressField field = AddressField.of(substring.charAt(1));
      // Accept only the first instance for any duplicate fields (which can occur because the
      // string we start with defines format order, which can contain duplicate fields).
      if (!visibleFields.contains(field)) {
        visibleFields.add(field);
        fieldOrder.add(field);
      }
    }
    applyFieldOrderOverrides(regionCode, fieldOrder);

    // Uses two address lines instead of street address.
    for (int n = 0; n < fieldOrder.size(); n++) {
      if (fieldOrder.get(n) == AddressField.STREET_ADDRESS) {
        fieldOrder.set(n, AddressField.ADDRESS_LINE_1);
        fieldOrder.add(n + 1, AddressField.ADDRESS_LINE_2);
        break;
      }
    }
    return Collections.unmodifiableList(fieldOrder);
  }

  /**
   * Returns a list of address fields based on the format of {@code regionCode} -- assuming script
   * type is {@link ScriptType#LOCAL}.
   */
  List<AddressField> getAddressFieldOrder(String regionCode) {
    Util.checkNotNull(regionCode);
    return getAddressFieldOrder(ScriptType.LOCAL, regionCode);
  }

  private void applyFieldOrderOverrides(String regionCode, List<AddressField> fieldOrder) {
    List<AddressField> customFieldOrder = formOptions.getCustomFieldOrder(regionCode);
    if (customFieldOrder == null) {
      return;
    }

    // We can assert that fieldOrder and customFieldOrder contain no duplicates.
    // We know this by the construction above and in FormOptions but we still have to think
    // about fields in the custom ordering which aren't visible (the loop below will fail if
    // a non-visible field appears in the custom ordering). However in that case it's safe to
    // just ignore the extraneous field.
    Set<AddressField> nonVisibleCustomFields = EnumSet.copyOf(customFieldOrder);
    nonVisibleCustomFields.removeAll(fieldOrder);
    if (nonVisibleCustomFields.size() > 0) {
      // Local mutable copy to remove non visible fields - this shouldn't happen often.
      customFieldOrder = new ArrayList<AddressField>(customFieldOrder);
      customFieldOrder.removeAll(nonVisibleCustomFields);
    }
    // It is vital for this loop to work correctly that every element in customFieldOrder
    // appears in fieldOrder exactly once.
    for (int fieldIdx = 0, customIdx = 0; fieldIdx < fieldOrder.size(); fieldIdx++) {
      if (customFieldOrder.contains(fieldOrder.get(fieldIdx))) {
        fieldOrder.set(fieldIdx, customFieldOrder.get(customIdx++));
      }
    }
  }

  /**
   * Returns the fields that are required to be filled in for this country. This is based upon the
   * "required" field in RegionDataConstants for {@code regionCode}, and handles falling back to
   * the default data if necessary.
   */
  static Set<AddressField> getRequiredFields(String regionCode) {
    Util.checkNotNull(regionCode);
    String requireString = getRequiredString(regionCode);

    EnumSet<AddressField> required = EnumSet.of(AddressField.COUNTRY);
    for (char c : requireString.toCharArray()) {
      required.add(AddressField.of(c));
    }
    return required;
  }

  private static String getRequiredString(String regionCode) {
    String required = getJsonValue(regionCode, AddressDataKey.REQUIRE);
    if (required == null) {
      required = getJsonValue("ZZ", AddressDataKey.REQUIRE);
    }
    return required;
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
        String normalizedStr = removeRedundantSpacesAndLeadingPunctuation(currentLine.toString());
        if (normalizedStr.length() > 0) {
          lines.add(normalizedStr);
          currentLine.setLength(0);
        }
      } else if (formatSymbol.startsWith("%")) {
        String value = null;
        switch (AddressField.of(formatSymbol.charAt(1))) {
          case STREET_ADDRESS:
            value =
                Util.joinAndSkipNulls("\n", address.getAddressLine1(), address.getAddressLine2());
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
   * Escaped tokens correspond to either new line or address fields. The output of this method
   * may contain duplicates.
   */
  // TODO: Create a common method which does field parsing in one place (there are about 4 other
  // places in this library where format strings are parsed).
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
          // Checks that the character is valid.
          AddressField.of(c);
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
      throw new RuntimeException("Invalid json for region code " + regionCode + ": " + jsonString);
    }
  }
}
