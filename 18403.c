void AutofillManager::ImportFormData(const FormStructure& submitted_form) {
  const CreditCard* imported_credit_card;
  if (!personal_data_->ImportFormData(submitted_form, &imported_credit_card))
    return;

  scoped_ptr<const CreditCard> scoped_credit_card(imported_credit_card);
  if (imported_credit_card && tab_contents()) {
    tab_contents_wrapper_->AddInfoBar(
        new AutofillCCInfoBarDelegate(tab_contents(),
                                      scoped_credit_card.release(),
                                      personal_data_,
                                      metric_logger_.get()));
  }
}
