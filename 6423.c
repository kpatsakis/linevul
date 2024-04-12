AtomicString GetInputModeAttribute(Element* element) {
  if (!element)
    return AtomicString();

  bool query_attribute = false;
  if (isHTMLInputElement(*element)) {
    query_attribute = toHTMLInputElement(*element).SupportsInputModeAttribute();
  } else if (isHTMLTextAreaElement(*element)) {
    query_attribute = true;
  } else {
    element->GetDocument().UpdateStyleAndLayoutTree();
    if (HasEditableStyle(*element))
      query_attribute = true;
  }

  if (!query_attribute)
    return AtomicString();

  return element->FastGetAttribute(HTMLNames::inputmodeAttr).DeprecatedLower();
}
