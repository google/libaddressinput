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

import com.android.i18n.addressinput.AddressField.WidthType;
import com.android.i18n.addressinput.AddressUiComponent.UiComponent;
import com.android.i18n.addressinput.LookupKey.KeyType;
import com.android.i18n.addressinput.LookupKey.ScriptType;

import java.text.Collator;
import java.util.ArrayList;
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
    private final EnumMap<AddressField, AddressUiComponent> mInputWidgets =
        new EnumMap<AddressField, AddressUiComponent>(AddressField.class);

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

    // The appropriate label that should be applied to the locality (city) field of the current
    // country.  Examples include "city" or "district".
    private String mLocalityLabel;

    // The appropriate label that should be applied to the admin area field of the current country.
    // Examples include "state", "province", "emirate", etc.
    private String mAdminLabel;

    private static final Map<String, Integer> ADMIN_LABELS;
    private static final Map<String, Integer> LOCALITY_LABELS;
    private static final Map<String, Integer> ADMIN_ERROR_MESSAGES;

    private static final FormOptions SHOW_ALL_FIELDS = new FormOptions.Builder().build();

    // The appropriate label that should be applied to the zip code field of the current country.
    private enum ZipLabel {
        ZIP,
        POSTAL
    }

    private ZipLabel mZipLabel;

    static {
        Map<String, Integer> adminLabelMap = new HashMap<String, Integer>(15);
        adminLabelMap.put("area", R.string.i18n_area);
        adminLabelMap.put("county", R.string.i18n_county_label);
        adminLabelMap.put("department", R.string.i18n_department);
        adminLabelMap.put("district", R.string.i18n_dependent_locality_label);
        adminLabelMap.put("do_si", R.string.i18n_do_si);
        adminLabelMap.put("emirate", R.string.i18n_emirate);
        adminLabelMap.put("island", R.string.i18n_island);
        adminLabelMap.put("oblast", R.string.i18n_oblast);
        adminLabelMap.put("parish", R.string.i18n_parish);
        adminLabelMap.put("prefecture", R.string.i18n_prefecture);
        adminLabelMap.put("province", R.string.i18n_province);
        adminLabelMap.put("state", R.string.i18n_state_label);
        ADMIN_LABELS = Collections.unmodifiableMap(adminLabelMap);

        Map<String, Integer> localityLabelMap = new HashMap<String, Integer>(2);
        localityLabelMap.put("city", R.string.i18n_locality_label);
        localityLabelMap.put("district", R.string.i18n_dependent_locality_label);
        LOCALITY_LABELS = Collections.unmodifiableMap(localityLabelMap);

        Map<String, Integer> adminErrorMap = new HashMap<String, Integer>(15);
        adminErrorMap.put("area", R.string.invalid_area);
        adminErrorMap.put("county", R.string.invalid_county_label);
        adminErrorMap.put("department", R.string.invalid_department);
        adminErrorMap.put("district", R.string.invalid_dependent_locality_label);
        adminErrorMap.put("do_si", R.string.invalid_do_si);
        adminErrorMap.put("emirate", R.string.invalid_emirate);
        adminErrorMap.put("island", R.string.invalid_island);
        adminErrorMap.put("oblast", R.string.invalid_oblast);
        adminErrorMap.put("parish", R.string.invalid_parish);
        adminErrorMap.put("prefecture", R.string.invalid_prefecture);
        adminErrorMap.put("province", R.string.invalid_province);
        adminErrorMap.put("state", R.string.invalid_state_label);
        ADMIN_ERROR_MESSAGES = Collections.unmodifiableMap(adminErrorMap);
    }

    // Need handler for callbacks to the UI thread
    final Handler mHandler = new Handler();

    final Runnable mUpdateMultipleFields = new Runnable() {
        @Override
        public void run() {
            updateFields();
        }
    };

    private class UpdateRunnable implements Runnable {
        private AddressField myId;

        public UpdateRunnable(AddressField id) {
            myId = id;
        }

        @Override
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

        @SuppressWarnings("unchecked")
        public AddressSpinnerInfo(Spinner view, AddressField id, AddressField parentId) {
            mView = view;
            mId = id;
            mParentId = parentId;
            mAdapter = (ArrayAdapter<String>) view.getAdapter();
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

    private final ArrayList<AddressSpinnerInfo> mSpinners = new ArrayList<AddressSpinnerInfo>();

    private AddressWidgetUiComponentProvider mComponentProvider;

    /** TODO: Add region-dependent width types for address fields. */
    private WidthType getFieldWidthType(AddressUiComponent field) {
        return field.getId().getDefaulWidthType();
    }

    private void createView(ViewGroup rootView, AddressUiComponent field, String defaultKey,
            boolean readOnly) {
        @SuppressWarnings("deprecation")  // FILL_PARENT renamed MATCH_PARENT in API Level 8.
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(LayoutParams.FILL_PARENT,
                LayoutParams.WRAP_CONTENT);
        String fieldText = field.getFieldName();
        WidthType widthType = getFieldWidthType(field);

        if (fieldText.length() > 0) {
            TextView textView = mComponentProvider.createUiLabel(fieldText, widthType);
            rootView.addView(textView, lp);
        }
        if (field.getUiType().equals(UiComponent.EDIT)) {
            EditText editText = mComponentProvider.createUiTextField(widthType);
            field.setView(editText);
            editText.setEnabled(!readOnly);
            rootView.addView(editText, lp);
        } else if (field.getUiType().equals(UiComponent.SPINNER)) {
            ArrayAdapter<String> adapter = mComponentProvider.createUiPickerAdapter(widthType);
            Spinner spinner = mComponentProvider.createUiPickerSpinner(widthType);

            field.setView(spinner);
            rootView.addView(spinner, lp);
            spinner.setAdapter(adapter);
            AddressSpinnerInfo spinnerInfo =
                    new AddressSpinnerInfo(spinner, field.getId(), field.getParentId());
            spinnerInfo.setSpinnerList(field.getCandidatesList(), defaultKey);

            if (fieldText.length() > 0) {
                spinner.setPrompt(fieldText);
            }
            spinner.setOnItemSelectedListener(this);
            mSpinners.add(spinnerInfo);
        }
    }

    /**
     *  Associates each field with its corresponding AddressUiComponent.
     */
    private void buildFieldWidgets() {
        AddressData data = new AddressData.Builder().setCountry(mCurrentRegion).build();
        LookupKey key = new LookupKey.Builder(LookupKey.KeyType.DATA).setAddressData(data).build();
        AddressVerificationNodeData countryNode =
            (new ClientData(mCacheData)).getDefaultData(key.toString());

        // Set up AddressField.ADMIN_AREA
        AddressUiComponent adminAreaUi = new AddressUiComponent(AddressField.ADMIN_AREA);
        adminAreaUi.setFieldName(getAdminAreaFieldName(countryNode));
        mInputWidgets.put(AddressField.ADMIN_AREA, adminAreaUi);

        // Set up AddressField.LOCALITY
        AddressUiComponent localityUi = new AddressUiComponent(AddressField.LOCALITY);
        localityUi.setFieldName(getLocalityFieldName(countryNode));
        mInputWidgets.put(AddressField.LOCALITY, localityUi);

        // Set up AddressField.DEPENDENT_LOCALITY
        AddressUiComponent subLocalityUi = new AddressUiComponent(AddressField.DEPENDENT_LOCALITY);
        subLocalityUi.setFieldName(mContext.getString(R.string.i18n_dependent_locality_label));
        mInputWidgets.put(AddressField.DEPENDENT_LOCALITY, subLocalityUi);

        // Set up AddressField.ADDRESS_LINE_1
        AddressUiComponent addressLine1Ui = new AddressUiComponent(AddressField.ADDRESS_LINE_1);
        addressLine1Ui.setFieldName(mContext.getString(R.string.i18n_address_line1_label));
        mInputWidgets.put(AddressField.ADDRESS_LINE_1, addressLine1Ui);

        // Set up AddressField.ADDRESS_LINE_2
        AddressUiComponent addressLine2Ui = new AddressUiComponent(AddressField.ADDRESS_LINE_2);
        addressLine2Ui.setFieldName("");
        mInputWidgets.put(AddressField.ADDRESS_LINE_2, addressLine2Ui);

        // Set up AddressField.ORGANIZATION
        AddressUiComponent organizationUi = new AddressUiComponent(AddressField.ORGANIZATION);
        organizationUi.setFieldName(mContext.getString(R.string.i18n_organization_label));
        mInputWidgets.put(AddressField.ORGANIZATION, organizationUi);

        // Set up AddressField.RECIPIENT
        AddressUiComponent recipientUi = new AddressUiComponent(AddressField.RECIPIENT);
        recipientUi.setFieldName(mContext.getString(R.string.i18n_recipient_label));
        mInputWidgets.put(AddressField.RECIPIENT, recipientUi);

        // Set up AddressField.POSTAL_CODE
        AddressUiComponent postalCodeUi = new AddressUiComponent(AddressField.POSTAL_CODE);
        postalCodeUi.setFieldName(getZipFieldName(countryNode));
        mInputWidgets.put(AddressField.POSTAL_CODE, postalCodeUi);

        // Set up AddressField.SORTING_CODE
        AddressUiComponent sortingCodeUi = new AddressUiComponent(AddressField.SORTING_CODE);
        sortingCodeUi.setFieldName("CEDEX");
        mInputWidgets.put(AddressField.SORTING_CODE, sortingCodeUi);
    }

    private void initializeDropDowns() {
        AddressUiComponent adminAreaUi = mInputWidgets.get(AddressField.ADMIN_AREA);
        List<RegionData> adminAreaList = getRegionData(AddressField.COUNTRY);
        adminAreaUi.initializeCandidatesList(adminAreaList);

        AddressUiComponent localityUi = mInputWidgets.get(AddressField.LOCALITY);
        List<RegionData> localityList = getRegionData(AddressField.ADMIN_AREA);
        localityUi.initializeCandidatesList(localityList);
    }

    // Zip code is called postal code in some countries. This method returns the appropriate name
    // for the given countryNode.
    private String getZipFieldName(AddressVerificationNodeData countryNode) {
        String zipName;
        String zipType = countryNode.get(AddressDataKey.ZIP_NAME_TYPE);
        if (zipType == null) {
            mZipLabel = ZipLabel.POSTAL;
            zipName = mContext.getString(R.string.i18n_postal_code_label);
        } else {
            mZipLabel = ZipLabel.ZIP;
            zipName = mContext.getString(R.string.i18n_zip_code_label);
        }
        return zipName;
    }

    private String getLocalityFieldName(AddressVerificationNodeData countryNode) {
        String localityLabelType = countryNode.get(AddressDataKey.LOCALITY_NAME_TYPE);
        mLocalityLabel = localityLabelType;
        Integer result = LOCALITY_LABELS.get(localityLabelType);
        if (result == null) {
            // Fallback to city.
            result = R.string.i18n_locality_label;
        }
        return mContext.getString(result);
    }

    private String getAdminAreaFieldName(AddressVerificationNodeData countryNode) {
        String adminLabelType = countryNode.get(AddressDataKey.STATE_NAME_TYPE);
        mAdminLabel = adminLabelType;
        Integer result = ADMIN_LABELS.get(adminLabelType);
        if (result == null) {
            // Fallback to province.
            result = R.string.i18n_province;
        }
        return mContext.getString(result);
    }

    private void buildCountryListBox() {
        // Set up AddressField.COUNTRY
        AddressUiComponent countryUi = new AddressUiComponent(AddressField.COUNTRY);
        countryUi.setFieldName(mContext.getString(R.string.i18n_country_label));
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
        countryUi.initializeCandidatesList(countries);
        mInputWidgets.put(AddressField.COUNTRY, countryUi);
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
            @Override
            public void dataLoadingBegin(){
            }

            @Override
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
            @Override
            public void dataLoadingBegin() {
                mProgressDialog = mComponentProvider.getUiActivityIndicatorView();
                mProgressDialog.setMessage(mContext.getString(R.string.address_data_loading));
                Log.d(this.toString(), "Progress dialog started.");
            }
            @Override
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
     * Creates an AddressWidget to be attached to rootView for the specific context using the
     * default UI component provider.
     */
    public AddressWidget(Context context, ViewGroup rootView, FormOptions formOptions,
            ClientCacheManager cacheManager) {
        this(context, rootView, formOptions, cacheManager,
                new AddressWidgetUiComponentProvider(context));
    }

    /**
     * Creates an AddressWidget to be attached to rootView for the specific context using UI
     * component provided by the provider.
     */
    public AddressWidget(Context context, ViewGroup rootView, FormOptions formOptions,
            ClientCacheManager cacheManager, AddressWidgetUiComponentProvider provider) {
        mComponentProvider = provider;
        mCurrentRegion =
            ((TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE))
                    .getSimCountryIso().toUpperCase(Locale.US);
        if (mCurrentRegion.length() == 0) {
            mCurrentRegion = "US";
        }
        init(context, rootView, formOptions, cacheManager);
        renderForm();
    }

    /**
     * Creates an AddressWidget to be attached to rootView for the specific context using the
     * default UI component provider, and fill out the address form with savedAddress.
     */
    public AddressWidget(Context context, ViewGroup rootView, FormOptions formOptions,
            ClientCacheManager cacheManager, AddressData savedAddress) {
        this(context, rootView, formOptions, cacheManager, savedAddress,
                new AddressWidgetUiComponentProvider(context));
    }

    /**
     * Creates an AddressWidget to be attached to rootView for the specific context using UI
     * component provided by the provider, and fill out the address form with savedAddress.
     */
    public AddressWidget(Context context, ViewGroup rootView, FormOptions formOptions,
            ClientCacheManager cacheManager, AddressData savedAddress,
            AddressWidgetUiComponentProvider provider) {
        mComponentProvider = provider;
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
            AddressUiComponent uiComponent = mInputWidgets.get(field);
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
            AddressUiComponent addressUiComponent = mInputWidgets.get(field);
            if (addressUiComponent != null) {
                String value = addressUiComponent.getValue();
                if (addressUiComponent.getUiType() == UiComponent.SPINNER) {
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
     * Gets the formatted address based on the AddressData passed in with none of the relevant
     * fields hidden.
     */
    public static List<String> getFullEnvelopeAddress(AddressData address) {
        return new FormatInterpreter(SHOW_ALL_FIELDS).getEnvelopeAddress(address);
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
        AddressUiComponent addressUiComponent = mInputWidgets.get(field);
        if (addressUiComponent != null && addressUiComponent.getUiType() == UiComponent.EDIT) {
            int errorMessageId = getErrorMessageIdForInvalidEntryIn(field);
            EditText view = (EditText) addressUiComponent.getView();
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
            AddressUiComponent addressUiComponent = mInputWidgets.get(field);

            if (addressUiComponent != null && addressUiComponent.getUiType() == UiComponent.EDIT) {
                EditText view = (EditText) addressUiComponent.getView();
                if (view != null) {
                    view.setError(null);
                }
            }
        }
    }

    public View getViewForField(AddressField field) {
      AddressUiComponent component = mInputWidgets.get(field);
      if (component == null) {
        return null;
      }
      return component.getView();
    }

    @Override
    public void onNothingSelected(AdapterView<?> arg0) {
    }

    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        updateChildNodes(parent, position);
    }
}
