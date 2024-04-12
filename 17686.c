bool PasswordAutofillAgent::PreviewSuggestion(
    const blink::WebFormControlElement& control_element,
    const blink::WebString& username,
    const blink::WebString& password) {
  const blink::WebInputElement* element = toWebInputElement(&control_element);
  if (!element)
    return false;

  blink::WebInputElement username_element;
  blink::WebInputElement password_element;
  PasswordInfo* password_info;

  if (!FindPasswordInfoForElement(*element, &username_element,
                                  &password_element, &password_info) ||
      (!username_element.isNull() &&
       !IsElementAutocompletable(username_element)) ||
      !IsElementAutocompletable(password_element)) {
    return false;
  }

  if (!element->isPasswordField() && !username_element.isNull()) {
    if (username_query_prefix_.empty())
      username_query_prefix_ = username_element.value();

    was_username_autofilled_ = username_element.isAutofilled();
    username_element.setSuggestedValue(username);
    username_element.setAutofilled(true);
    form_util::PreviewSuggestion(username_element.suggestedValue(),
                                 username_query_prefix_, &username_element);
  }
  was_password_autofilled_ = password_element.isAutofilled();
  password_element.setSuggestedValue(password);
  password_element.setAutofilled(true);

  return true;
}
