  void TestClearSectionWithNode(const char* html, bool unowned) {
    LoadHTML(html);
    WebLocalFrame* web_frame = GetMainFrame();
    ASSERT_NE(nullptr, web_frame);

    FormCache form_cache(web_frame);
    std::vector<FormData> forms = form_cache.ExtractNewForms();
    ASSERT_EQ(1U, forms.size());

    WebInputElement firstname = GetInputElementById("firstname");
    firstname.SetAutofillState(WebAutofillState::kAutofilled);
    WebInputElement lastname = GetInputElementById("lastname");
    lastname.SetAutofillState(WebAutofillState::kAutofilled);
    WebInputElement month = GetInputElementById("month");
    month.SetAutofillState(WebAutofillState::kAutofilled);
    WebFormControlElement textarea = GetFormControlElementById("textarea");
    textarea.SetAutofillState(WebAutofillState::kAutofilled);

    WebInputElement notenabled = GetInputElementById("notenabled");
    notenabled.SetValue(WebString::FromUTF8("no clear"));

    EXPECT_TRUE(form_cache.ClearSectionWithElement(firstname));

    EXPECT_FALSE(firstname.IsAutofilled());

    FormData form;
    FormFieldData field;
    EXPECT_TRUE(
        FindFormAndFieldForFormControlElement(firstname, &form, &field));
    EXPECT_EQ(GetCanonicalOriginForDocument(web_frame->GetDocument()),
              form.origin);
    EXPECT_FALSE(form.origin.is_empty());
    if (!unowned) {
      EXPECT_EQ(ASCIIToUTF16("TestForm"), form.name);
      EXPECT_EQ(GURL("http://abc.com"), form.action);
    }

    const std::vector<FormFieldData>& fields = form.fields;
    ASSERT_EQ(9U, fields.size());

    FormFieldData expected;
    expected.form_control_type = "text";
    expected.max_length = WebInputElement::DefaultMaxLength();

    expected.id_attribute = ASCIIToUTF16("firstname");
    expected.name = expected.id_attribute;
    expected.value.clear();
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[0]);

    expected.id_attribute = ASCIIToUTF16("lastname");
    expected.name = expected.id_attribute;
    expected.value.clear();
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[1]);

    expected.id_attribute = ASCIIToUTF16("noAC");
    expected.name = expected.id_attribute;
    expected.value = ASCIIToUTF16("one");
    expected.label = ASCIIToUTF16("one");
    expected.autocomplete_attribute = "off";
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[2]);
    expected.autocomplete_attribute.clear();

    expected.id_attribute = ASCIIToUTF16("notenabled");
    expected.name = expected.id_attribute;
    expected.value = ASCIIToUTF16("no clear");
    expected.label.clear();
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[3]);

    expected.form_control_type = "month";
    expected.max_length = 0;
    expected.id_attribute = ASCIIToUTF16("month");
    expected.name = expected.id_attribute;
    expected.value.clear();
    expected.label.clear();
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[4]);

    expected.id_attribute = ASCIIToUTF16("month-disabled");
    expected.name = expected.id_attribute;
    expected.value = ASCIIToUTF16("2012-11");
    expected.label = ASCIIToUTF16("2012-11");
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[5]);

    expected.form_control_type = "textarea";
    expected.id_attribute = ASCIIToUTF16("textarea");
    expected.name = expected.id_attribute;
    expected.value.clear();
    expected.label.clear();
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[6]);

    expected.id_attribute = ASCIIToUTF16("textarea-disabled");
    expected.name = expected.id_attribute;
    expected.value = ASCIIToUTF16("    Banana!  ");
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[7]);

    expected.id_attribute = ASCIIToUTF16("textarea-noAC");
    expected.name = expected.id_attribute;
    expected.value = ASCIIToUTF16("Carrot?");
    expected.autocomplete_attribute = "off";
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[8]);
    expected.autocomplete_attribute.clear();

    EXPECT_EQ(0, firstname.SelectionStart());
    EXPECT_EQ(0, firstname.SelectionEnd());
  }
