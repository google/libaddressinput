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

import android.app.ProgressDialog;
import android.content.Context;
import android.os.Handler;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.LinearLayout.LayoutParams;
import android.widget.Spinner;
import android.widget.TextView;

import com.android.i18n.addressinput.AddressUIComponent.UIComponent;
import com.android.i18n.addressinput.LookupKey.KeyType;
import com.android.i18n.addressinput.LookupKey.ScriptType;

import java.util.ArrayList;
import java.text.Collator;
import java.util.Collections;
import java.util.EnumMap;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * Address widget that lays out address fields, validate and format addresses according to local
 * customs.
 */
public class AddressWidget implements AdapterView.OnItemSelectedListener {
    private Context mContext;

    private ViewGroup mRootView;

    private LayoutInflater mInflater;

    private CacheData mCacheData;

    // A map for all address fields except for country.
    private final EnumMap<AddressField, AddressUIComponent> mInputWidgets =
        new EnumMap<AddressField, AddressUIComponent>(AddressField.class);

    private FormController mFormController;

    private FormatInterpreter mFormatInterpreter;

    private FormOptions mFormOptions;

    private StandardAddressVerifier mVerifier;

    private ProgressDialog mProgressDialog;

    private String mCurrentRegion;

    // The current language the widget use in BCP47 format. It differs from the default locale of
    // the phone in that it contains information on the script to use.
    private String mWidgetLocale;

    private ScriptType mScript;

    // The appropriate label that should be applied to the admin area field of the current country.
    // Examples include "state", "province", "emirate", etc.
    private String mAdminLabel;

    private static final Map<String, Integer> ADMIN_LABELS;
    private static final Map<String, Integer> ADMIN_ERROR_MESSAGES;

    // The appropriate label that should be applied to the zip code field of the current country.
    private enum ZipLabel {
        ZIP,
        POSTAL
    }

    private ZipLabel mZipLabel;

    static {
        Map<String, Integer> adminLabelMap = new HashMap<String, Integer>(15);
        adminLabelMap.put("state", R.string.state_label);
        adminLabelMap.put("province", R.string.province);
        adminLabelMap.put("prefecture", R.string.prefecture);
        adminLabelMap.put("parish", R.string.parish);
        adminLabelMap.put("island", R.string.island);
        adminLabelMap.put("emirate", R.string.emirate);
        adminLabelMap.put("department", R.string.department);
        adminLabelMap.put("county", R.string.county_label);
        adminLabelMap.put("area", R.string.area);
        adminLabelMap.put("do_si", R.string.do_si);
        ADMIN_LABELS = Collections.unmodifiableMap(adminLabelMap);

        Map<String, Integer> adminErrorMap = new HashMap<String, Integer>(15);
        adminErrorMap.put("state", R.string.invalid_state_label);
        adminErrorMap.put("province", R.string.invalid_province);
        adminErrorMap.put("prefecture", R.string.invalid_prefecture);
        adminErrorMap.put("parish", R.string.invalid_parish);
        adminErrorMap.put("island", R.string.invalid_island);
        adminErrorMap.put("emirate", R.string.invalid_emirate);
        adminErrorMap.put("department", R.string.invalid_department);
        adminErrorMap.put("county", R.string.invalid_county_label);
        adminErrorMap.put("area", R.string.invalid_area);
        adminErrorMap.put("do_si", R.string.invalid_do_si);
        ADMIN_ERROR_MESSAGES = Collections.unmodifiableMap(adminErrorMap);
    }

    // Need handler for callbacks to the UI thread
    final Handler mHandler = new Handler();

    final Runnable mUpdateMultipleFields = new Runnable() {
        public void run() {
            updateFields();
        }
    };

    private class UpdateRunnable implements Runnable {
        private AddressField myId;

        public UpdateRunnable(AddressField id) {
            myId = id;
        }

        public void run() {
            updateInputWidget(myId);
        }
    }

    private static class AddressSpinnerInfo {
        private Spinner mView;

        private AddressField mId;

        private AddressField mParentId;

        private ArrayAdapter<String> mAdapter;

        private List<RegionData> mCurrentRegions;

        public AddressSpinnerInfo(Spinner view, AddressField id, AddressField parentId) {
            mView = view;
            mId = id;
            mParentId = parentId;
        }

        // Initializes the adapter that manages the Spinner.
        public void initAdapter(Context context, int textViewId, int dropDownId) {
            mAdapter = new ArrayAdapter<String>(context, textViewId);
            mAdapter.setDropDownViewResource(dropDownId);
        }

        public void setSpinnerList(List<RegionData> list, String defaultKey) {
            mCurrentRegions = list;
            mAdapter.clear();
            for (RegionData item : list) {
                mAdapter.add(item.getDisplayName());
            }
            mAdapter.sort(Collator.getInstance(Locale.getDefault()));
            if (defaultKey.length() == 0) {
                mView.setSelection(0);
            } else {
                int position = mAdapter.getPosition(defaultKey);
                mView.setSelection(position);
            }
        }

        // Returns the region key of the currently selected region in the Spinner.
        public String getRegionCode(int position) {
            if (mAdapter.getCount() <= position) {
                return "";
            }
            String value = mAdapter.getItem(position);
            return getRegionDataKeyForValue(value);
        }

        // Returns the region key for the region value.
        public String getRegionDataKeyForValue(String value) {
            for (RegionData data : mCurrentRegions) {
                if (data.getDisplayName().endsWith(value)) {
                    return data.getKey();
                }
            }
            return "";
        }
    }

    private ArrayList<AddressSpinnerInfo> mSpinners = new ArrayList<AddressSpinnerInfo>();

    private void createView(ViewGroup rootView, AddressUIComponent field, String defaultKey,
            boolean readOnly) {
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(LayoutParams.FILL_PARENT,
                LayoutParams.WRAP_CONTENT);
        String fieldText = field.getFieldName();

        if (fieldText.length() > 0) {
            TextView textView = (TextView) mInflater.inflate(R.layout.address_textview, rootView,
                    false);
            rootView.addView(textView, lp);
            textView.setText(fieldText);
        }
        if (field.getUIType().equals(UIComponent.EDIT)) {
            View view = mInflater.inflate(R.layout.address_edittext, rootView, false);
            field.setView(view);
            EditText editText = (EditText) view;
            editText.setEnabled(!readOnly);
            rootView.addView(editText, lp);
        } else if (field.getUIType().equals(UIComponent.SPINNER)) {
            View view = mInflater.inflate(R.layout.address_spinner, rootView, false);
            field.setView(view);
            Spinner spinner = (Spinner) view;
            rootView.addView(spinner, lp);
            AddressSpinnerInfo spinnerInfo =
                new AddressSpinnerInfo(spinner, field.getId(), field.getParentId());
            spinnerInfo.initAdapter(mContext, android.R.layout.simple_spinner_item,
                    android.R.layout.simple_spinner_dropdown_item);
            spinner.setAdapter(spinnerInfo.mAdapter);
            spinnerInfo.setSpinnerList(field.getCandidatesList(), defaultKey);

            if (fieldText.length() > 0) {
                spinner.setPrompt(fieldText);
            }
            spinner.setOnItemSelectedListener(this);
            mSpinners.add(spinnerInfo);
        }
    }

    /**
     *  Associates each field with its corresponding AddressUIComponent.
     */
    private void buildFieldWidgets() {
        AddressData data = new AddressData.Builder().setCountry(mCurrentRegion).build();
        LookupKey key = new LookupKey.Builder(LookupKey.KeyType.DATA).setAddressData(data).build();
        AddressVerificationNodeData countryNode =
            (new ClientData(mCacheData)).getDefaultData(key.toString());

        // Set up AddressField.ADMIN_AREA
        AddressUIComponent adminAreaUI = new AddressUIComponent(AddressField.ADMIN_AREA);
        adminAreaUI.setFieldName(getAdminAreaFieldName(countryNode));
        mInputWidgets.put(AddressField.ADMIN_AREA, adminAreaUI);

        // Set up AddressField.LOCALITY
        AddressUIComponent localityUI = new AddressUIComponent(AddressField.LOCALITY);
        localityUI.setFieldName(mContext.getString(R.string.locality_label));
        mInputWidgets.put(AddressField.LOCALITY, localityUI);

        // Set up AddressField.DEPENDENT_LOCALITY
        AddressUIComponent subLocalityUI = new AddressUIComponent(AddressField.DEPENDENT_LOCALITY);
        subLocalityUI.setFieldName(mContext.getString(R.string.dependent_locality_label));
        mInputWidgets.put(AddressField.DEPENDENT_LOCALITY, subLocalityUI);

        // Set up AddressField.ADDRESS_LINE_1
        AddressUIComponent addressLine1UI = new AddressUIComponent(AddressField.ADDRESS_LINE_1);
        addressLine1UI.setFieldName(mContext.getString(R.string.address_line1_label));
        mInputWidgets.put(AddressField.ADDRESS_LINE_1, addressLine1UI);

        // Set up AddressField.ADDRESS_LINE_2
        AddressUIComponent addressLine2UI = new AddressUIComponent(AddressField.ADDRESS_LINE_2);
        addressLine2UI.setFieldName("");
        mInputWidgets.put(AddressField.ADDRESS_LINE_2, addressLine2UI);

        // Set up AddressField.ORGANIZATION
        AddressUIComponent organizationUI = new AddressUIComponent(AddressField.ORGANIZATION);
        organizationUI.setFieldName(mContext.getString(R.string.organization_label));
        mInputWidgets.put(AddressField.ORGANIZATION, organizationUI);

        // Set up AddressField.RECIPIENT
        AddressUIComponent recipientUI = new AddressUIComponent(AddressField.RECIPIENT);
        recipientUI.setFieldName(mContext.getString(R.string.recipient_label));
        mInputWidgets.put(AddressField.RECIPIENT, recipientUI);

        // Set up AddressField.POSTAL_CODE
        AddressUIComponent postalCodeUI = new AddressUIComponent(AddressField.POSTAL_CODE);
        postalCodeUI.setFieldName(getZipFieldName(countryNode));
        mInputWidgets.put(AddressField.POSTAL_CODE, postalCodeUI);

        // Set up AddressField.SORTING_CODE
        AddressUIComponent sortingCodeUI = new AddressUIComponent(AddressField.SORTING_CODE);
        sortingCodeUI.setFieldName("CEDEX");
        mInputWidgets.put(AddressField.SORTING_CODE, sortingCodeUI);
    }

    private void initializeDropDowns() {
        AddressUIComponent adminAreaUI = mInputWidgets.get(AddressField.ADMIN_AREA);
        List<RegionData> adminAreaList = getRegionData(AddressField.COUNTRY);
        adminAreaUI.initializeCandidatesList(adminAreaList);

        AddressUIComponent localityUI = mInputWidgets.get(AddressField.LOCALITY);
        List<RegionData> localityList = getRegionData(AddressField.ADMIN_AREA);
        localityUI.initializeCandidatesList(localityList);
    }

    // Zip code is called postal code in some countries. This method returns the appropriate name
    // for the given countryNode.
    private String getZipFieldName(AddressVerificationNodeData countryNode) {
        String zipName;
        String zipType = countryNode.get(AddressDataKey.ZIP_NAME_TYPE);
        if (zipType == null) {
            mZipLabel = ZipLabel.POSTAL;
            zipName = mContext.getString(R.string.postal_code_label);
        } else {
            mZipLabel = ZipLabel.ZIP;
            zipName = mContext.getString(R.string.zip_code_label);
        }
        return zipName;
    }

    private String getAdminAreaFieldName(AddressVerificationNodeData countryNode) {
        String adminLabelType = countryNode.get(AddressDataKey.STATE_NAME_TYPE);
        mAdminLabel = adminLabelType;
        Integer result = ADMIN_LABELS.get(adminLabelType);
        if (result == null) {
            // Fallback to province.
            result = R.string.province;
        }
        return mContext.getString(result);
    }

    private void buildCountryListBox() {
        // Set up AddressField.COUNTRY
        AddressUIComponent countryUI = new AddressUIComponent(AddressField.COUNTRY);
        countryUI.setFieldName(mContext.getString(R.string.country_label));
        ArrayList<RegionData> countries = new ArrayList<RegionData>();
        for (RegionData regionData : mFormController.getRegionData(new LookupKey.Builder(
                KeyType.DATA).build())) {
            String regionKey = regionData.getKey();
            // ZZ represents an unknown region code.
            if (!regionKey.equals("ZZ")) {
                String localCountryName = getLocalCountryName(regionKey);
                RegionData country = new RegionData.Builder().setKey(regionKey).setName(
                        localCountryName).build();
                countries.add(country);
            }
        }
        countryUI.initializeCandidatesList(countries);
        mInputWidgets.put(AddressField.COUNTRY, countryUI);
    }

    private String getLocalCountryName(String regionCode) {
        return (new Locale("", regionCode)).getDisplayCountry(Locale.getDefault());
    }

    private AddressSpinnerInfo findSpinnerByView(View view) {
        for (AddressSpinnerInfo spinnerInfo : mSpinners) {
            if (spinnerInfo.mView == view) {
                return spinnerInfo;
            }
        }
        return null;
    }

    private void updateFields() {
        removePreviousViews();
        buildFieldWidgets();
        initializeDropDowns();
        layoutAddressFields();
    }

    private void removePreviousViews() {
        if (mRootView == null) {
            return;
        }
        int childCount = mRootView.getChildCount();
        if (mFormOptions.isHidden(AddressField.COUNTRY)) {
            if (childCount > 0) {
                mRootView.removeAllViews();
            }
        } else if (childCount > 2) {
            // Keep the TextView and Spinner for Country and remove everything else.
            mRootView.removeViews(2, mRootView.getChildCount() - 2);
        }
    }

    private void layoutAddressFields() {
        for (AddressField field : mFormatInterpreter.getAddressFieldOrder(mScript,
                mCurrentRegion)) {
            if (!mFormOptions.isHidden(field)) {
              createView(mRootView, mInputWidgets.get(field), "", mFormOptions.isReadonly(field));
            }
        }
    }

    private void updateChildNodes(AdapterView<?> parent, int position) {
        AddressSpinnerInfo spinnerInfo = findSpinnerByView(parent);
        if (spinnerInfo == null) {
            return;
        }

        // Find all the child spinners, if any, that depend on this one.
        final AddressField myId = spinnerInfo.mId;
        if (myId != AddressField.COUNTRY && myId != AddressField.ADMIN_AREA
                && myId != AddressField.LOCALITY) {
            // Only a change in the three AddressFields above will trigger a change in other
            // AddressFields. Therefore, for all other AddressFields, we return immediately.
            return;
        }

        String regionCode = spinnerInfo.getRegionCode(position);
        if (myId == AddressField.COUNTRY) {
            updateWidgetOnCountryChange(regionCode);
            return;
        }

        mFormController.requestDataForAddress(getAddressData(), new DataLoadListener() {
            public void dataLoadingBegin(){
            }

            public void dataLoadingEnd() {
                Runnable updateChild = new UpdateRunnable(myId);
                mHandler.post(updateChild);
            }
        });
    }

    public void updateWidgetOnCountryChange(String regionCode) {
        if (mCurrentRegion.equalsIgnoreCase(regionCode)) {
            return;
        }
        mCurrentRegion = regionCode;
        mFormController.setCurrentCountry(mCurrentRegion);
        renderForm();
    }

    private void updateInputWidget(AddressField myId) {
        for (AddressSpinnerInfo child : mSpinners) {
            if (child.mParentId == myId) {
                List<RegionData> candidates = getRegionData(child.mParentId);
                child.setSpinnerList(candidates, "");
            }
        }
    }

    public void renderForm() {
        setWidgetLocaleAndScript();
        AddressData data = new AddressData.Builder().setCountry(mCurrentRegion)
                .setLanguageCode(mWidgetLocale).build();
        mFormController.requestDataForAddress(data, new DataLoadListener() {
            public void dataLoadingBegin() {
                mProgressDialog = ProgressDialog.show(mContext, "",
                        mContext.getString(R.string.address_data_loading));
                Log.d(this.toString(), "Progress dialog started.");
            };
            public void dataLoadingEnd() {
                Log.d(this.toString(), "Data loading completed.");
                mProgressDialog.dismiss();
                Log.d(this.toString(), "Progress dialog stopped.");
                mHandler.post(mUpdateMultipleFields);
            }
        });
    }

    private void setWidgetLocaleAndScript() {
        mWidgetLocale = Util.getWidgetCompatibleLanguageCode(Locale.getDefault(), mCurrentRegion);
        mFormController.setLanguageCode(mWidgetLocale);
        mScript = Util.isExplicitLatinScript(mWidgetLocale)
                ? ScriptType.LATIN
                : ScriptType.LOCAL;
    }

    private List<RegionData> getRegionData(AddressField parentField) {
        AddressData address = getAddressData();

        // Removes language code from address if it is default. This address is used to build
        // lookup key, which neglects default language. For example, instead of "data/US--en/CA",
        // the right lookup key is "data/US/CA".
        if (mFormController.isDefaultLanguage(address.getLanguageCode())) {
            address = new AddressData.Builder(address).setLanguageCode(null).build();
        }

        LookupKey parentKey = mFormController.getDataKeyFor(address).getKeyForUpperLevelField(
                parentField);
        List<RegionData> candidates;
        // Can't build a key with parent field, quit.
        if (parentKey == null) {
            Log.w(this.toString(), "Can't build key with parent field " + parentField + ". One of"
                    + " the ancestor fields might be empty");

            // Removes candidates that exist from previous settings. For example, data/US has a
            // list of candidates AB, BC, CA, etc, that list should be cleaned up when user updates
            // the address by changing country to Channel Islands.
            candidates = new ArrayList<RegionData>(1);
        } else {
            candidates = mFormController.getRegionData(parentKey);
        }
        return candidates;
    }

    /**
     * Creates an AddressWidget to be attached to rootView for the specific context.
     */
    public AddressWidget(Context context, ViewGroup rootView, FormOptions formOptions,
            ClientCacheManager cacheManager) {
        mCurrentRegion =
            ((TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE))
                    .getSimCountryIso().toUpperCase();
        if (mCurrentRegion.length() == 0) {
            mCurrentRegion = "US";
        }
        init(context, rootView, formOptions, cacheManager);
        renderForm();
    }

    /**
     * Creates an AddressWidget to be attached to rootView for the specific context, and fill out
     * the address form with savedAddress.
     */
    public AddressWidget(Context context, ViewGroup rootView, FormOptions formOptions,
            ClientCacheManager cacheManager, AddressData savedAddress) {
        mCurrentRegion = savedAddress.getPostalCountry();
        // Postal country must be 2 letter country code. Otherwise default to US.
        if (mCurrentRegion == null || mCurrentRegion.length() != 2) {
            mCurrentRegion = "US";
        }
        init(context, rootView, formOptions, cacheManager);
        renderFormWithSavedAddress(savedAddress);
    }

    public void renderFormWithSavedAddress(AddressData savedAddress) {
        setWidgetLocaleAndScript();
        removePreviousViews();
        buildFieldWidgets();
        layoutAddressFields();
        initializeFieldsWithAddress(savedAddress);
    }

    private void initializeFieldsWithAddress(AddressData savedAddress) {
        for (AddressField field : mFormatInterpreter.getAddressFieldOrder(mScript,
                mCurrentRegion)) {
            String value = savedAddress.getFieldValue(field);
            if (value == null) {
                value = "";
            }
            AddressUIComponent uiComponent = mInputWidgets.get(field);
            EditText view = (EditText) uiComponent.getView();
            if (view != null) {
               view.setText(value);
            }
        }
    }

    private void init(Context context, ViewGroup rootView, FormOptions formOptions,
            ClientCacheManager cacheManager) {
        mContext = context;
        mRootView = rootView;
        mFormOptions = formOptions;
        mCacheData = new CacheData(cacheManager);
        mInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        mFormController =
            new FormController(new ClientData(mCacheData),
                               mWidgetLocale, mCurrentRegion);
        mFormatInterpreter = new FormatInterpreter(mFormOptions);
        mVerifier = new StandardAddressVerifier(
                new FieldVerifier(new ClientData(mCacheData)));
        if (!formOptions.isHidden(AddressField.COUNTRY)) {
            buildCountryListBox();
            createView(mRootView, mInputWidgets.get(AddressField.COUNTRY),
                    getLocalCountryName(mCurrentRegion),
                    formOptions.isReadonly(AddressField.COUNTRY));
        }
    }

    /**
     * Sets address data server URL. Input URL cannot be null.
     *
     * @param url The service URL.
     */
    public void setUrl(String url) {
        mCacheData.setUrl(url);
    }

    /**
     * Gets user input address in AddressData format.
     */
    public AddressData getAddressData() {
        AddressData.Builder builder = new AddressData.Builder();
        builder.setCountry(mCurrentRegion);
        for (AddressField field : mFormatInterpreter.getAddressFieldOrder(mScript,
                mCurrentRegion)) {
            AddressUIComponent addressUIComponent = mInputWidgets.get(field);
            if (addressUIComponent != null) {
                String value = addressUIComponent.getValue();
                if (addressUIComponent.getUIType() == UIComponent.SPINNER) {
                     // For drop-downs, return the key of the region selected instead of the value.
                     View view = getViewForField(field);
                     AddressSpinnerInfo spinnerInfo = findSpinnerByView(view);
                     if (spinnerInfo != null) {
                         value = spinnerInfo.getRegionDataKeyForValue(value);
                     }
                }
                builder.set(field, value);
            }
        }
        builder.setLanguageCode(mWidgetLocale);
        return builder.build();
    }

    /**
     * Gets the formatted address.
     *
     * This method does not validate addresses. Also, it will "normalize" the result strings by
     * removing redundant spaces and empty lines.
     *
     * @return the formatted address
     */
    public List<String> getEnvelopeAddress() {
        return mFormatInterpreter.getEnvelopeAddress(getAddressData());
    }

    /**
     * Gets the formatted address based on the AddressData passed in.
     */
    public List<String> getEnvelopeAddress(AddressData address) {
        return mFormatInterpreter.getEnvelopeAddress(address);
    }

    /**
     * Get problems found in the address data entered by the user.
     */
    public AddressProblems getAddressProblems() {
        AddressProblems problems = new AddressProblems();
        AddressData addressData = getAddressData();
        mVerifier.verify(addressData, problems);
        return problems;
    }

    /**
     * Displays an appropriate error message when the AddressField contains an invalid entry.
     *
     * @return the View object representing the AddressField.
     */
    public View displayErrorMessageForInvalidEntryIn(AddressField field) {
        Log.d(this.toString(), "Display error message for the field: " + field.toString());
        AddressUIComponent addressUIComponent = mInputWidgets.get(field);
        if (addressUIComponent != null && addressUIComponent.getUIType() == UIComponent.EDIT) {
            int errorMessageId = getErrorMessageIdForInvalidEntryIn(field);
            EditText view = (EditText) addressUIComponent.getView();
            view.setError(mContext.getString(errorMessageId));
            return view;
        }
        return null;
    }

    private int getErrorMessageIdForInvalidEntryIn(AddressField field) {
        switch (field) {
            case ADMIN_AREA:
                return ADMIN_ERROR_MESSAGES.get(mAdminLabel);
            case LOCALITY:
                return R.string.invalid_locality_label;
            case DEPENDENT_LOCALITY:
                return R.string.invalid_dependent_locality_label;
            case POSTAL_CODE:
                return (mZipLabel == ZipLabel.POSTAL
                        ? R.string.invalid_postal_code_label
                        : R.string.invalid_zip_code_label);
            default:
                return R.string.invalid_entry;
        }
    }

    /**
     * Clears all error messages in the UI.
     */
    public void clearErrorMessage() {
        for (AddressField field : mFormatInterpreter.getAddressFieldOrder(mScript,
                mCurrentRegion)) {
            AddressUIComponent addressUIComponent = mInputWidgets.get(field);

            if (addressUIComponent != null && addressUIComponent.getUIType() == UIComponent.EDIT) {
                EditText view = (EditText) addressUIComponent.getView();
                if (view != null) {
                    view.setError(null);
                }
            }
        }
    }

    public View getViewForField(AddressField field) {
      AddressUIComponent component = mInputWidgets.get(field);
      if (component == null) {
        return null;
      }
      return component.getView();
    }

    public void onNothingSelected(AdapterView<?> arg0) {
    }

    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        updateChildNodes(parent, position);
    }
}
