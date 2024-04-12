bool HTMLFormControlElement::isRequired() const {
  return fastHasAttribute(requiredAttr);
}
