String AXNodeObject::valueDescription() const {
  if (!supportsRangeValue())
    return String();

  return getAOMPropertyOrARIAAttribute(AOMStringProperty::kValueText)
      .getString();
}
