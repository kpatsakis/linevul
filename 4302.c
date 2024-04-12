void AutofillExternalDelegate::OnCreditCardScanned(const CreditCard& card) {
  manager_->FillCreditCardForm(query_id_, query_form_, query_field_, card,
                               base::string16());
}
