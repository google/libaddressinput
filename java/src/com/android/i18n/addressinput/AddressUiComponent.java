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

import android.view.View;
import android.widget.EditText;
import android.widget.Spinner;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a component in the address widget UI. It could be either a text box (when there is no
 * candidate) or a spinner.
 */
class AddressUiComponent {
    // The label for the UI component
    private String mFieldName;

    // The type of the UI component
    private UiComponent mUiType;

    // The list of elements in the UI component
    private List<RegionData> mCandidatesList = new ArrayList<RegionData>();

    // The id of this UI component
    private AddressField mId;

    // The id of the parent UI component. When the parent UI component is updated, this UI
    // component should be updated.
    private AddressField mParentId;

    // The View representing the UI component
    private View mView;

    /**
     * Type of UI component. There are only EDIT (text-box) and SPINNER (drop-down) components.
     */
    enum UiComponent {
        EDIT, SPINNER,
    }

    AddressUiComponent(AddressField id) {
        mId = id;
        // By default, an AddressUiComponent doesn't depend on anything else.
        mParentId = null;
        mUiType = UiComponent.EDIT;
    }

    /**
     * Initializes the candidatesList, and set the uiType and parentId.
     * @param candidatesList
     */
    void initializeCandidatesList(List<RegionData> candidatesList) {
        mCandidatesList = candidatesList;
        if (candidatesList.size() > 1) {
            mUiType = UiComponent.SPINNER;
            switch (mId) {
                case DEPENDENT_LOCALITY:
                    mParentId = AddressField.LOCALITY;
                    break;
                case LOCALITY:
                    mParentId = AddressField.ADMIN_AREA;
                    break;
                case ADMIN_AREA:
                    mParentId = AddressField.COUNTRY;
                    break;
                default:
                    // Ignore.
            }
        }
    }

    /**
     * Gets the value entered in the UI component.
     */
    String getValue() {
        if (mView == null) {
            return (mCandidatesList.size() == 0) ? "" : mCandidatesList.get(0).getDisplayName();
        }
        switch (mUiType) {
            case SPINNER:
                Object selectedItem = ((Spinner) mView).getSelectedItem();
                if (selectedItem == null) {
                    return "";
                }
                return selectedItem.toString();
            case EDIT:
                return ((EditText) mView).getText().toString();
            default:
                return "";
        }
    }

    String getFieldName() {
        return mFieldName;
    }

    void setFieldName(String fieldName) {
        mFieldName = fieldName;
    }

    UiComponent getUiType() {
        return mUiType;
    }

    void setUiType(UiComponent uiType) {
        mUiType = uiType;
    }

    List<RegionData> getCandidatesList() {
        return mCandidatesList;
    }

    void setCandidatesList(List<RegionData> candidatesList) {
        mCandidatesList = candidatesList;
    }

    AddressField getId() {
        return mId;
    }

    void setId(AddressField id) {
        mId = id;
    }

    AddressField getParentId() {
        return mParentId;
    }

    void setParentId(AddressField parentId) {
        mParentId = parentId;
    }

    void setView(View view) {
        mView = view;
    }

    View getView() {
        return mView;
    }
}
