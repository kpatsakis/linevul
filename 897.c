bool PasswordAutofillAgent::FindPasswordInfoForElement(
    const WebInputElement& element,
    WebInputElement* username_element,
    WebInputElement* password_element,
    PasswordInfo** password_info) {
  DCHECK(username_element && password_element && password_info);
  username_element->Reset();
  password_element->Reset();
  if (!element.IsPasswordFieldForAutofill()) {
    *username_element = element;
  } else {
    if (!sent_request_to_store_) {
      SendPasswordForms(false);
      return false;
    }

    *password_element = element;

    auto iter = web_input_to_password_info_.find(element);
    if (iter == web_input_to_password_info_.end()) {
      PasswordToLoginMap::const_iterator password_iter =
          password_to_username_.find(element);
      if (password_iter == password_to_username_.end()) {
        if (web_input_to_password_info_.empty())
          return false;
        iter = last_supplied_password_info_iter_;
      } else {
        *username_element = password_iter->second;
      }
    }

    if (iter != web_input_to_password_info_.end()) {
      *username_element = FindUsernameElementPrecedingPasswordElement(
          render_frame()->GetWebFrame(), *password_element);
      *password_info = &iter->second;
      return true;
    }
  }

  auto iter = web_input_to_password_info_.find(*username_element);
  if (iter == web_input_to_password_info_.end())
    return false;

  *password_info = &iter->second;
  if (password_element->IsNull())
    *password_element = (*password_info)->password_field;

  return true;
}
