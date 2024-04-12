  void CreateTestCreditCardFormData(FormData* form,
                                    bool is_https,
                                    bool use_month_type) {
    form->name = ASCIIToUTF16("MyForm");
    if (is_https) {
      form->origin = GURL("https://myform.com/form.html");
      form->action = GURL("https://myform.com/submit.html");
    } else {
      form->origin = GURL("http://myform.com/form.html");
      form->action = GURL("http://myform.com/submit.html");
    }

    FormFieldData field;
    test::CreateTestFormField("Name on Card", "nameoncard", "", "text", &field);
    form->fields.push_back(field);
    test::CreateTestFormField("Card Number", "cardnumber", "", "text", &field);
    form->fields.push_back(field);
    if (use_month_type) {
      test::CreateTestFormField("Expiration Date", "ccmonth", "", "month",
                                &field);
      form->fields.push_back(field);
    } else {
      test::CreateTestFormField("Expiration Date", "ccmonth", "", "text",
                                &field);
      form->fields.push_back(field);
      test::CreateTestFormField("", "ccyear", "", "text", &field);
      form->fields.push_back(field);
    }
    test::CreateTestFormField("CVC", "cvc", "", "text", &field);
    form->fields.push_back(field);
  }
