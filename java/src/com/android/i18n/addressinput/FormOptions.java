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

import java.util.Arrays;
import java.util.Collections;
import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Configuration options for the address input widget used to control the visibility and interaction
 * of specific fields to suit specific use cases (eg, collecting business addresses, collecting
 * addresses for credit card verification etc...).
 * <p>
 * Also, provides the ability to add additional required fields, for e.g. {@link
 * AddressField#RECIPIENT}.
 */
public final class FormOptions {

  // These fields must never be null).
  private final EnumSet<AddressField> hiddenFields;
  private final EnumSet<AddressField> readonlyFields;

  // Key is ISO 2-letter region code.
  private Map<String, List<AddressField>> customFieldOrder =
      new HashMap<String, List<AddressField>>();

  private final EnumMap<AddressField, String> customLabels =
      new EnumMap<AddressField, String>(AddressField.class);

  private final EnumSet<AddressField> requiredFields;

  private final EnumMap<AddressField, Integer> maxLengths =
      new EnumMap<AddressField, Integer>(AddressField.class);

  private final String serverUrl;

  private FormOptions(Builder builder) {
    // copy values from builder
    hiddenFields = EnumSet.copyOf(builder.hiddenFields);
    readonlyFields = EnumSet.copyOf(builder.readonlyFields);
    requiredFields = EnumSet.copyOf(builder.requiredFields);
    customLabels.putAll(builder.customLabels);
    customFieldOrder.putAll(builder.customFieldOrder);
    maxLengths.putAll(builder.maxLengths);
    serverUrl = builder.serverUrl;
  }


  boolean isHidden(AddressField field) {
    return hiddenFields.contains(field);
  }

  boolean isReadonly(AddressField field) {
    return readonlyFields.contains(field);
  }

  boolean isRequired(AddressField field) {
    return requiredFields.contains(field);
  }

  EnumSet<AddressField> getRequiredFields() {
    return requiredFields;
  }

  /**
   * Gets the customized label for the {@code field}, or returns null if none.
   */
  String getCustomLabel(AddressField field) {
    return customLabels.get(field);
  }

  /**
   * Gets the URL of the Address Data Server.
   */
  String getUrl() {
    return serverUrl;
  }

  /**
   * Gets the overridden field orders with their corresponding region code. Returns null if field
   * orders for {@code regionCode} is not specified.
   */
  List<AddressField> getCustomFieldOrder(String regionCode) {
    return customFieldOrder.get(regionCode);
  }

  /**
   * Gets the customized max length for the {@code field}, or null if none.
   */
  int getCustomMaxLength(AddressField field) {
    return maxLengths.get(field);
  }

  /**
   * Class to build the form, specifying the attributes for each field.
   */
  public static class Builder {

    private final EnumSet<AddressField> requiredFields =
        EnumSet.noneOf(AddressField.class);

    private final EnumSet<AddressField> hiddenFields =
        EnumSet.noneOf(AddressField.class);

    private final EnumSet<AddressField> readonlyFields =
        EnumSet.noneOf(AddressField.class);

    private final EnumMap<AddressField, String> customLabels =
        new EnumMap<AddressField, String>(AddressField.class);

    private final Map<String, List<AddressField>> customFieldOrder =
        new HashMap<String, List<AddressField>>();

    private final EnumMap<AddressField, Integer> maxLengths =
        new EnumMap<AddressField, Integer>(AddressField.class);

    /**
     * Uses the default server URL from CacheData.
     */
    private String serverUrl = new CacheData().getUrl();

    public Builder hide(AddressField field) {
      if (field == null) {
        throw new RuntimeException("AddressField field cannot be null.");
      }
      hiddenFields.add(field);
      return this;
    }

    /**
     * Make a field read-only.
     */
    public Builder readonly(AddressField field) {
      if (field == null) {
        throw new RuntimeException("AddressField field cannot be null.");
      }
      readonlyFields.add(field);
      return this;
    }

    /**
     * Make a field required.
     */
    public Builder required(AddressField field) {
      if (field == null) {
        throw new RuntimeException("AddressField field cannot be null.");
      }
      requiredFields.add(field);
      return this;
    }

    /**
     * Customizes label for an {@code AddressField}.
     */
    public Builder customizeLabel(AddressField field, String label) {
      if (field == null) {
        throw new RuntimeException("AddressField field cannot be null.");
      }
      if (label == null) {
        throw new RuntimeException("Label cannot be null.");
      }
      customLabels.put(field, label);
      return this;
    }

    /**
     * Sets the order of address input fields for the given ISO 3166-1 two letter country code.
     * <p>
     * Input fields affected by custom ordering will be shown in the widget in the order they are
     * given to this method (for the associated region code). Fields which are visible for a region,
     * but which are not specified here, will appear in their original position in the form. For
     * example, if a region defines the following fields:
     * <pre>
     * [ RECIPIENT -> ORGANIZATION -> STREET_ADDRESS -> LOCALITY -> ADMIN_AREA -> COUNTRY ]
     * </pre>
     * and the custom ordering for that region is (somewhat contrived):
     * <pre>
     * [ ORGANIZATION -> COUNTRY -> RECIPIENT ]
     * </pre>
     * Then the visible order of the input fields will be:
     * <pre>
     * [ ORGANIZATION -> COUNTRY -> STREET_ADDRESS -> LOCALITY -> ADMIN_AREA -> RECIPIENT ]
     * </pre>
     * <ul>
     * <li>Fields not specified in the custom ordering (STREET_ADDRESS, LOCALITY, ADMIN_AREA)
     * remain in their original, absolute, positions.
     * <li>Custom ordered fields are re-positioned such that their relative order is now as
     * specified (but other, non custom-ordered, fields can appear between them).
     * </ul>
     * <p>
     * If the custom order contains a field which is not present for the specified region, it is
     * silently ignored. Setting a custom ordering can never be used as a way to add fields for a
     * region.
     * <p>
     * Typically this feature is used to reverse things like RECIPIENT and ORGANIZATION for certain
     * business related use cases. It should not be used to "correct" perceived bad field ordering
     * or make different countries "more consistent with each other".
     */
    public Builder customizeFieldOrder(String regionCode, AddressField... fields) {
      // TODO: Consider checking the given region code for validity against RegionDataConstants.
      List<AddressField> fieldList = Collections.unmodifiableList(Arrays.asList(fields));
      if (fieldList.size() > 0) {
        if (EnumSet.copyOf(fieldList).size() != fieldList.size()) {
          throw new IllegalArgumentException("duplicate address field: " + fieldList);
        }
        customFieldOrder.put(regionCode, fieldList);
      } else {
        customFieldOrder.remove(regionCode);
      }
      return this;
    }

    /**
     * Sets the URL of address data server. {@code url} cannot be null. This url will override
     * the default address server url.
     */
    public Builder setUrl(String url) {
      if (url == null) {
        throw new RuntimeException("Can't set address server URL to null.");
      }
      serverUrl = url;
      return this;
    }

    /**
     * Customizes max length for a {@code AddressField}.
     */
    public Builder customizeMaxLength(AddressField field, int maxLength) {
      if (field == null) {
        throw new RuntimeException("AddressField field cannot be null.");
      }
      maxLengths.put(field, maxLength);
      return this;
    }

    public FormOptions build() {
      return new FormOptions(this);
    }
  }
}
