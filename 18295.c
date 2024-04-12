bool HTMLInputElement::StepMismatch() const {
  return willValidate() && input_type_->StepMismatch(value());
}
