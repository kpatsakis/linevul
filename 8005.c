WebTextInputType InputMethodController::TextInputType() const {
  if (!GetFrame().Selection().IsAvailable()) {
    return kWebTextInputTypeNone;
  }

  if (!RootEditableElementOfSelection(GetFrame().Selection()))
    return kWebTextInputTypeNone;

  if (!IsAvailable())
    return kWebTextInputTypeNone;

  Element* element = GetDocument().FocusedElement();
  if (!element)
    return kWebTextInputTypeNone;

  if (isHTMLInputElement(*element)) {
    HTMLInputElement& input = toHTMLInputElement(*element);
    const AtomicString& type = input.type();

    if (input.IsDisabledOrReadOnly())
      return kWebTextInputTypeNone;

    if (type == InputTypeNames::password)
      return kWebTextInputTypePassword;
    if (type == InputTypeNames::search)
      return kWebTextInputTypeSearch;
    if (type == InputTypeNames::email)
      return kWebTextInputTypeEmail;
    if (type == InputTypeNames::number)
      return kWebTextInputTypeNumber;
    if (type == InputTypeNames::tel)
      return kWebTextInputTypeTelephone;
    if (type == InputTypeNames::url)
      return kWebTextInputTypeURL;
    if (type == InputTypeNames::text)
      return kWebTextInputTypeText;

    return kWebTextInputTypeNone;
  }

  if (isHTMLTextAreaElement(*element)) {
    if (toHTMLTextAreaElement(*element).IsDisabledOrReadOnly())
      return kWebTextInputTypeNone;
    return kWebTextInputTypeTextArea;
  }

  if (element->IsHTMLElement()) {
    if (ToHTMLElement(element)->IsDateTimeFieldElement())
      return kWebTextInputTypeDateTimeField;
  }

  GetDocument().UpdateStyleAndLayoutTree();
  if (HasEditableStyle(*element))
    return kWebTextInputTypeContentEditable;

  return kWebTextInputTypeNone;
}
