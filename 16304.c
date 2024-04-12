  void CreateTestCreditCards() {
    CreditCard credit_card1;
    test::SetCreditCardInfo(&credit_card1, "Elvis Presley",
                            "4234567890123456",  // Visa
                            "04", "2999", "1");
    credit_card1.set_guid("00000000-0000-0000-0000-000000000004");
    credit_card1.set_use_count(10);
    credit_card1.set_use_date(AutofillClock::Now() -
                              base::TimeDelta::FromDays(5));
    personal_data_.AddCreditCard(credit_card1);

    CreditCard credit_card2;
    test::SetCreditCardInfo(&credit_card2, "Buddy Holly",
                            "5187654321098765",  // Mastercard
                            "10", "2998", "1");
    credit_card2.set_guid("00000000-0000-0000-0000-000000000005");
    credit_card2.set_use_count(5);
    credit_card2.set_use_date(AutofillClock::Now() -
                              base::TimeDelta::FromDays(4));
    personal_data_.AddCreditCard(credit_card2);

    CreditCard credit_card3;
    test::SetCreditCardInfo(&credit_card3, "", "", "", "", "");
    credit_card3.set_guid("00000000-0000-0000-0000-000000000006");
    personal_data_.AddCreditCard(credit_card3);
  }
