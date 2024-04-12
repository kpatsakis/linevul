bool HTMLFormElement::hasLegalLinkAttribute(const QualifiedName& name) const {
  return name == actionAttr || HTMLElement::hasLegalLinkAttribute(name);
}
