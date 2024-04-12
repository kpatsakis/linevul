void PaymentRequestState::SetDefaultProfileSelections() {
  if (!contact_profiles().empty() &&
      profile_comparator()->IsContactInfoComplete(contact_profiles_[0]))
    selected_contact_profile_ = contact_profiles()[0];

  const std::vector<std::unique_ptr<PaymentInstrument>>& instruments =
      available_instruments();
  auto first_complete_instrument =
      std::find_if(instruments.begin(), instruments.end(),
                   [](const std::unique_ptr<PaymentInstrument>& instrument) {
                     return instrument->IsCompleteForPayment() &&
                            instrument->IsExactlyMatchingMerchantRequest();
                   });
  selected_instrument_ = first_complete_instrument == instruments.end()
                             ? nullptr
                             : first_complete_instrument->get();

  SelectDefaultShippingAddressAndNotifyObservers();

  bool has_complete_instrument =
      available_instruments().empty()
          ? false
          : available_instruments()[0]->IsCompleteForPayment();

  journey_logger_->SetNumberOfSuggestionsShown(
      JourneyLogger::Section::SECTION_PAYMENT_METHOD,
      available_instruments().size(), has_complete_instrument);
}
