void PaymentRequestState::OnSWPaymentInstrumentValidated(
    ServiceWorkerPaymentInstrument* instrument,
    bool result) {
  if (!result) {
    for (size_t i = 0; i < available_instruments_.size(); i++) {
      if (available_instruments_[i].get() == instrument) {
        available_instruments_.erase(available_instruments_.begin() + i);
        break;
      }
    }
  }

  if (--number_of_pending_sw_payment_instruments_ > 0)
    return;

  FinishedGetAllSWPaymentInstruments();
}
