void AutofillMetricsTest::RecreateMaskedServerCreditCardWithBankName() {
  personal_data_->ClearCreditCards();
  CreditCard credit_card(CreditCard::MASKED_SERVER_CARD, "server_id");
  test::SetCreditCardInfo(&credit_card, "name", "1111" /* Visa */, "01", "2999",
                          "");
  credit_card.set_guid("10000000-0000-0000-0000-000000000002");
  credit_card.SetNetworkForMaskedCard(kVisaCard);
  credit_card.set_bank_name("Chase");
  personal_data_->AddServerCreditCard(credit_card);
  personal_data_->Refresh();
}
