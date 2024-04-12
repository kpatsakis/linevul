  void TestClearSectionWithNodeContainingSelectOne(const char* html,
                                                   bool unowned) {
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

    WebSelectElement state =
        web_frame->GetDocument().GetElementById("state").To<WebSelectElement>();
    state.SetValue(WebString::FromUTF8("AK"));
    state.SetAutofillState(WebAutofillState::kAutofilled);

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
    ASSERT_EQ(3U, fields.size());

    FormFieldData expected;

    expected.id_attribute = ASCIIToUTF16("firstname");
    expected.name = expected.id_attribute;
    expected.value.clear();
    expected.form_control_type = "text";
    expected.max_length = WebInputElement::DefaultMaxLength();
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[0]);

    expected.id_attribute = ASCIIToUTF16("lastname");
    expected.name = expected.id_attribute;
    expected.value.clear();
    expected.form_control_type = "text";
    expected.max_length = WebInputElement::DefaultMaxLength();
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[1]);

    expected.id_attribute = ASCIIToUTF16("state");
    expected.name_attribute = ASCIIToUTF16("state");
    expected.name = expected.name_attribute;
    expected.value = ASCIIToUTF16("?");
    expected.form_control_type = "select-one";
    expected.max_length = 0;
    EXPECT_FORM_FIELD_DATA_EQUALS(expected, fields[2]);

    EXPECT_EQ(0, firstname.SelectionStart());
    EXPECT_EQ(0, firstname.SelectionEnd());
  }
