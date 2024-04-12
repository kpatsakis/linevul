void HTMLFormElement::InvalidateDefaultButtonStyle() const {
  for (const auto& control : ListedElements()) {
    if (!control->IsFormControlElement())
      continue;
    if (ToHTMLFormControlElement(control)->CanBeSuccessfulSubmitButton()) {
      ToHTMLFormControlElement(control)->PseudoStateChanged(
          CSSSelector::kPseudoDefault);
    }
  }
}
