void PasswordAutofillAgent::OnProvisionallySaveForm(
    const WebFormElement& form,
    const WebFormControlElement& element,
    ElementChangeSource source) {
  if (source == ElementChangeSource::SELECT_CHANGED)
    return;

  WebInputElement input_element;
  if (!element.IsNull() && element.HasHTMLTagName("input"))
    input_element = *ToWebInputElement(&element);

  if (source == ElementChangeSource::TEXTFIELD_CHANGED) {
    DCHECK(!input_element.IsNull());
    UpdateStateForTextChange(input_element);
    return;
  }

  DCHECK_EQ(ElementChangeSource::WILL_SEND_SUBMIT_EVENT, source);
  ProvisionallySavePassword(form, input_element,
                            RESTRICTION_NON_EMPTY_PASSWORD);
}
