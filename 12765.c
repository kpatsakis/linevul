void HTMLInputElement::DispatchChangeEventIfNeeded() {
  if (isConnected() && input_type_->ShouldSendChangeEventAfterCheckedChanged())
    DispatchChangeEvent();
}
