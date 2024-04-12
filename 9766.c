bool PaymentRequestState::IsInitialized() const {
  return get_all_instruments_finished_;
}
