bool InputType::RangeUnderflow(const String& value) const {
  if (!IsSteppable())
    return false;

  const Decimal numeric_value = ParseToNumberOrNaN(value);
  if (!numeric_value.IsFinite())
    return false;

  return numeric_value < CreateStepRange(kRejectAny).Minimum();
}
