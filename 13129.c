void PasswordAutofillAgent::UpdateStateForTextChange(
    const WebInputElement& element) {
  if (!element.IsTextField())
    return;
  WebInputElement mutable_element = element;  // We need a non-const.

  const base::string16 element_value = element.Value().Utf16();
  field_data_manager_.UpdateFieldDataMap(element, element_value,
                                         FieldPropertiesFlags::USER_TYPED);

  ProvisionallySavePassword(element.Form(), element, RESTRICTION_NONE);

  if (element.IsPasswordFieldForAutofill()) {
    auto iter = password_to_username_.find(element);
    if (iter != password_to_username_.end()) {
      web_input_to_password_info_[iter->second].password_was_edited_last = true;
      mutable_element.SetAutofillState(WebAutofillState::kNotFilled);
    }
    GetPasswordManagerDriver()->UserModifiedPasswordField();
  } else {
    GetPasswordManagerDriver()->UserModifiedNonPasswordField(
        element.UniqueRendererFormControlId(), element_value);
  }
}
