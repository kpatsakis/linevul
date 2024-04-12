const AtomicString& HTMLFormControlElement::autocapitalize() const {
  if (!FastGetAttribute(kAutocapitalizeAttr).IsEmpty())
    return HTMLElement::autocapitalize();

  if (HTMLFormElement* form = Form())
    return form->autocapitalize();

  return g_empty_atom;
}
