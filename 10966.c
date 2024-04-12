std::string PaymentRequestState::GetAuthenticatedEmail() const {
  return payment_request_delegate_->GetAuthenticatedEmail();
}
