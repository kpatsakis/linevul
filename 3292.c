void HTMLFormControlElement::Reset() {
  SetAutofillState(WebAutofillState::kNotFilled);
  ResetImpl();
}
