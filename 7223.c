inline void HTMLInputElement::RemoveFromRadioButtonGroup() {
  if (RadioButtonGroupScope* scope = GetRadioButtonGroupScope())
    scope->RemoveButton(this);
}
