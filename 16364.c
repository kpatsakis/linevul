HTMLFormControlElement::HTMLFormControlElement(const QualifiedName& tag_name,
                                               Document& document)
    : HTMLElement(tag_name, document),
      autofill_state_(WebAutofillState::kNotFilled),
      blocks_form_submission_(false) {
  SetHasCustomStyleCallbacks();
  static unsigned next_free_unique_id = 0;
  unique_renderer_form_control_id_ = next_free_unique_id++;
}
