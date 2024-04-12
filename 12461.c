bool HTMLInputElement::HasLegalLinkAttribute(const QualifiedName& name) const {
  return input_type_->HasLegalLinkAttribute(name) ||
         TextControlElement::HasLegalLinkAttribute(name);
}
