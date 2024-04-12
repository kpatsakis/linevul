bool HTMLInputElement::MatchesReadOnlyPseudoClass() const {
  return input_type_->SupportsReadOnly() && IsReadOnly();
}
