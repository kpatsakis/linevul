bool IsInPasswordFieldWithUnrevealedPassword(const Position& position) {
  TextControlElement* text_control = EnclosingTextControl(position);
  if (!isHTMLInputElement(text_control))
    return false;
  HTMLInputElement* input = toHTMLInputElement(text_control);
  return (input->type() == InputTypeNames::password) &&
         !input->ShouldRevealPassword();
}
