// Copyright 2010 Google Inc. All Rights Reserved.

package com.android.i18n.addressinput;

import android.view.View;
import android.widget.EditText;
import android.widget.Spinner;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a component in the address widget UI. It could be either a text box (when there is no
 * candidate) or a select box.
 */
public class AddressUIComponent {
    // The label for the UI component
    private String mFieldName;

    // The type of the UI component
    private UIComponent mUiType;

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
    public enum UIComponent {
        EDIT, SPINNER,
    }

    public AddressUIComponent(AddressField id) {
        mId = id;
        // By default, an AddressUIComponent doesn't depend on anything else.
        mParentId = null;
        mUiType = UIComponent.EDIT;
    }

    /**
     * Initializes the candidatesList, and set the uiType and parentId.
     * @param candidatesList
     */
    public void initializeCandidatesList(List<RegionData> candidatesList) {
        this.mCandidatesList = candidatesList;
        if (candidatesList.size() > 1) {
            mUiType = UIComponent.SPINNER;
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
            }
        }
    }

    /**
     * Gets the value entered in the UI component.
     */
    public String getValue() {
        if (mView == null) {
            return (mCandidatesList.size() == 0) ? "" : mCandidatesList.get(0).getName();
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

    public String getFieldName() {
        return mFieldName;
    }

    public void setFieldName(String fieldName) {
        mFieldName = fieldName;
    }

    public UIComponent getUIType() {
        return mUiType;
    }

    public void setUIType(UIComponent uiType) {
        mUiType = uiType;
    }

    public List<RegionData> getCandidatesList() {
        return mCandidatesList;
    }

    public void setCandidatesList(List<RegionData> candidatesList) {
        mCandidatesList = candidatesList;
    }

    public AddressField getId() {
        return mId;
    }

    public void setId(AddressField id) {
        mId = id;
    }

    public AddressField getParentId() {
        return mParentId;
    }

    public void setParentId(AddressField parentId) {
        mParentId = parentId;
    }

    public void setView(View view) {
        mView = view;
    }

    public View getView() {
        return mView;
    }
}
