void PaymentRequestState::SetSelectedInstrument(PaymentInstrument* instrument) {
  selected_instrument_ = instrument;
  UpdateIsReadyToPayAndNotifyObservers();
}
