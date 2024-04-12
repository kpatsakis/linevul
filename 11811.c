void InputType::SetValueAsDate(double, ExceptionState& exception_state) const {
  exception_state.ThrowDOMException(
      kInvalidStateError, "This input element does not support Date values.");
}
