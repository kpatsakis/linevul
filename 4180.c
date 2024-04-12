void AutofillManager::FillCreditCardFormField(const CreditCard* credit_card,
                                              AutofillFieldType type,
                                              webkit_glue::FormField* field) {
  DCHECK(credit_card);
  DCHECK_EQ(AutofillType::CREDIT_CARD, AutofillType(type).group());
  DCHECK(field);

  if (field->form_control_type == ASCIIToUTF16("select-one")) {
    autofill::FillSelectControl(*credit_card, type, field);
  } else if (field->form_control_type == ASCIIToUTF16("month")) {
    string16 year = credit_card->GetInfo(CREDIT_CARD_EXP_4_DIGIT_YEAR);
    string16 month = credit_card->GetInfo(CREDIT_CARD_EXP_MONTH);
    if (!year.empty() && !month.empty()) {
      field->value = year + ASCIIToUTF16("-") + month;
    }
  } else {
    string16 value = credit_card->GetInfo(type);
    if (type == CREDIT_CARD_NUMBER)
      value = CreditCard::StripSeparators(value);
    field->value = value;
  }
}
