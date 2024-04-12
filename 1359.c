void PaymentRequest::OnShippingOptionIdSelected(
    std::string shipping_option_id) {
  client_->OnShippingOptionChange(shipping_option_id);
}
