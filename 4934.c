void AutofillManager::FillOrPreviewCreditCardForm(
    AutofillDriver::RendererFormDataAction action,
    int query_id,
    const FormData& form,
    const FormFieldData& field,
    const CreditCard& credit_card) {
  FormStructure* form_structure = nullptr;
  AutofillField* autofill_field = nullptr;
  if (!GetCachedFormAndField(form, field, &form_structure, &autofill_field))
    return;
  if (action == AutofillDriver::FORM_DATA_ACTION_FILL) {
    if (credit_card.record_type() == CreditCard::MASKED_SERVER_CARD &&
        WillFillCreditCardNumber(form, field)) {
      unmasking_query_id_ = query_id;
      unmasking_form_ = form;
      unmasking_field_ = field;
      masked_card_ = credit_card;
      payments::FullCardRequest* full_card_request =
          CreateFullCardRequest(form_structure->form_parsed_timestamp());
      full_card_request->GetFullCard(
          masked_card_, AutofillClient::UNMASK_FOR_AUTOFILL,
          weak_ptr_factory_.GetWeakPtr(), weak_ptr_factory_.GetWeakPtr());
      credit_card_form_event_logger_->OnDidSelectMaskedServerCardSuggestion(
          form_structure->form_parsed_timestamp());
      return;
    }
    credit_card_form_event_logger_->OnDidFillSuggestion(
        credit_card, *form_structure, *autofill_field);
  }

  FillOrPreviewDataModelForm(
      action, query_id, form, field, credit_card, /*is_credit_card=*/true,
      /*cvc=*/base::string16(), form_structure, autofill_field);
}
