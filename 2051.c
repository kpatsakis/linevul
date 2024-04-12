double InputType::Minimum() const {
  return CreateStepRange(kRejectAny).Minimum().ToDouble();
}
