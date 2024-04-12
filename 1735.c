ServiceWorkerPaymentInstrument::~ServiceWorkerPaymentInstrument() {
  if (delegate_ && !needs_installation_) {
    content::PaymentAppProvider::GetInstance()->AbortPayment(
        browser_context_, stored_payment_app_info_->registration_id,
        base::DoNothing());
  }
}
