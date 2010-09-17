// Copyright 2010 Google Inc. All Rights Reserved.

package com.android.i18n.addressinput;

import android.view.View;
import android.widget.EditText;
import android.widget.Spinner;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a component in the address widget UI. It could be either a text
 * box (when there is no candidate) or a select box.
 */
public class AddressUIComponent {
    // The label for the UI component
    private String fieldName;

    // The type of the UI component
    private UIComponent uiType;

    // The list of elements in the UI component
    private List<RegionData> candidatesList = new ArrayList<RegionData>();

    // The id of this UI component
    private AddressField id;

    // The id of the parent UI component. When the parent UI component is updated, this UI
    // component should be updated.
    private AddressField parentId;

    // The View representing the UI component
    private View view;

    public enum UIComponent {
        EDIT, SPINNER,
    }

    public AddressUIComponent(AddressField id) {
        this.id = id;
        // By default, an AddressUIComponent doesn't depend on anything else.
        parentId = null;
        uiType = UIComponent.EDIT;
    }

    /**
     * Initialize the candidatesList, and set the uiType and parentId
     * @param candidatesList
     */
    public void initializeCandidatesList(List<RegionData> candidatesList) {
        this.candidatesList = candidatesList;
        if (candidatesList.size() > 1) {
            uiType = UIComponent.SPINNER;
            switch (id) {
                case DEPENDENT_LOCALITY:
                    parentId = AddressField.LOCALITY;
                    break;
                case LOCALITY:
                    parentId = AddressField.ADMIN_AREA;
                    break;
                case ADMIN_AREA:
                    parentId = AddressField.COUNTRY;
                    break;
            }
        }
    }

    /**
     * Get the value entered in the UI component
     */
    public String getValue() {
        if (view == null) {
            return (candidatesList.size() == 0) ? "" : candidatesList.get(0).getName();
        }
        switch (uiType) {
            case SPINNER:
                Object selectedItem = ((Spinner) view).getSelectedItem();
                if (selectedItem == null) {
                    return "";
                }
                return selectedItem.toString();
            case EDIT:
                return ((EditText) view).getText().toString();
            default:
                return "";
        }
    }

    public String getFieldName() {
        return fieldName;
    }

    public void setFieldName(String fieldName) {
        this.fieldName = fieldName;
    }

    public UIComponent getUIType() {
        return uiType;
    }

    public void setUIType(UIComponent uiType) {
        this.uiType = uiType;
    }

    public List<RegionData> getCandidatesList() {
        return candidatesList;
    }

    public void setCandidatesList(List<RegionData> candidatesList) {
        this.candidatesList = candidatesList;
    }

    public AddressField getId() {
        return id;
    }

    public void setId(AddressField id) {
        this.id = id;
    }

    public AddressField getParentId() {
        return parentId;
    }

    public void setParentId(AddressField parentId) {
        this.parentId = parentId;
    }

    public void setView(View view) {
        this.view = view;
    }

    public View getView() {
        return view;
    }
}
