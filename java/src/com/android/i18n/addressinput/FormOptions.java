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

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

/**
 * Configuration Options that can be used by Address Display components for things like show/hide
 * fields or make them readonly. By default, all the fields are visible and editable.
 *
 * <p>Also, provides the ability to add additional required fields, for e.g. {@link
 * AddressField#RECIPIENT}.
 */
public class FormOptions {

  private final String baseId;

  private final EnumSet<AddressField> hiddenFields;

  private final EnumSet<AddressField> readonlyFields;

  private final EnumSet<AddressField> requiredFields;

  private final EnumMap<AddressField, String> customLabels =
      new EnumMap<AddressField, String>(AddressField.class);

  private final Map<String, AddressField[]> overrideFieldOrder =
      new HashMap<String, AddressField[]>();

  private final EnumMap<AddressField, Integer> maxLengths =
      new EnumMap<AddressField, Integer>(AddressField.class);

  private final String serverUrl;

  private FormOptions(Builder builder) {
    // copy values from builder
    baseId = builder.baseId;
    hiddenFields = EnumSet.copyOf(builder.hiddenFields);
    readonlyFields = EnumSet.copyOf(builder.readonlyFields);
    requiredFields = EnumSet.copyOf(builder.requiredFields);
    customLabels.putAll(builder.customLabels);
    overrideFieldOrder.putAll(builder.overrideFieldOrder);
    maxLengths.putAll(builder.maxLengths);
    serverUrl = builder.serverUrl;
  }

  /**
   * Gets base ID of the address form. Default is "addressform".
   */
  String getBaseId() {
    return baseId;
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
  AddressField[] getCustomFieldOrder(String regionCode) {
    if (regionCode == null) {
      throw new RuntimeException("regionCode cannot be null.");
    }
    return overrideFieldOrder.get(regionCode);
  }

  /**
   * Gets the customized max length for the {@code field}, or null if none.
   */
  Integer getCustomMaxLength(AddressField field) {
    return maxLengths.get(field);
  }

  /**
   * Class to build the form, specifying the attributes for each field.
   */
  public static class Builder {

    private String baseId = "addressform";

    private final EnumSet<AddressField> requiredFields =
        EnumSet.noneOf(AddressField.class);

    private final EnumSet<AddressField> hiddenFields =
        EnumSet.noneOf(AddressField.class);

    private final EnumSet<AddressField> readonlyFields =
        EnumSet.noneOf(AddressField.class);

    private final EnumMap<AddressField, String> customLabels =
        new EnumMap<AddressField, String>(AddressField.class);

    private final Map<String, AddressField[]> overrideFieldOrder =
        new HashMap<String, AddressField[]>();

    private final EnumMap<AddressField, Integer> maxLengths =
        new EnumMap<AddressField, Integer>(AddressField.class);

    /**
     * Uses the default server URL from CacheData.
     */
    private String serverUrl = new CacheData().getUrl();

    /**
     * Sets the base ID of the address form.
     */
    public Builder baseId(String baseId) {
      if (baseId == null) {
        throw new RuntimeException("baseId cannot be null.");
      }
      this.baseId = baseId;
      return this;
    }

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
     * Sets the field order for a region code. The order you set here will override the
     * predefined one. For example, you can set field order for US to be first {@code
     * AddressField#ORGANIZATION} then {@code AddressField#RECIPIENT}. Repeated address fields
     * in {@code fields} are not allowed. Size of {@code fields} has to be larger than one.
     * Input {@code fields} can be partial or even contain field not needed in the specified
     * {@code regionCode}. For example, German addresses contain the following fields
     * (in order):<br/>
     {@link AddressField#RECIPIENT}, {@link AddressField#ORGANIZATION}, {@link
     * AddressField#STREET_ADDRESS}, {@link AddressField#POSTAL_CODE}, {@link
     * AddressField#LOCALITY}. <br/>
     *
     * <p>With the following call: <br/>
     *
     * customizeFieldOrder("DE", AddressField.ORGANIZATION, AddressField.RECIPIENT,
     * AddressField.ADMIN_AREA);
     *
     * <p>Field order for Germany will become: <br/> {@link AddressField#ORGANIZATION}, {@link
     * AddressField#RECIPIENT}, {@link AddressField#STREET_ADDRESS}, {@link
     * AddressField#POSTAL_CODE}, {@link AddressField#LOCALITY}. </p>
     *
     * <p>Notice that:<br/> <ol> <li>{@link AddressField#ORGANIZATION} comes before {@link
     * AddressField#RECIPIENT} after reordering.</li>
     * <li>Fields not specified stays the same.</li>
     * <li>{@link AddressField#ADMIN_AREA} is specified but since it is not in German address
     * format, it is simpled neglected.</li> </ol>
     *
     * @param fields the overridden field order.
     */
    public Builder customizeFieldOrder(String regionCode, AddressField... fields) {
      if (regionCode == null) {
        throw new RuntimeException("regionCode cannot be null.");
      }
      if (fields == null) {
        throw new RuntimeException("Fields cannot be null.");
      }
      if (fields.length <= 1) {
        throw new RuntimeException("There must be more than one field.");
      }
      HashSet<AddressField> checkList = new HashSet<AddressField>();
      AddressField[] f = new AddressField[fields.length];
      int i = 0;
      for (AddressField field : fields) {
        // Can't contain repeated address fields.
        if (checkList.contains(field)) {
          throw new RuntimeException("Address fields cannot be repeated.");
        }
        checkList.add(field);
        f[i] = field;
        i++;
      }
      overrideFieldOrder.put(regionCode, f);
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
