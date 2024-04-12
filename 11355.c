  void TryBasicFormFill() {
    FocusFirstNameField();

    LOG(WARNING) << "Typing 'M' to bring up the Autofill popup.";
    SendKeyToPageAndWait(ui::VKEY_M);

    LOG(WARNING) << "Simulating down arrow press to initiate Autofill preview.";
    SendKeyToPopupAndWait(ui::VKEY_DOWN);

    ExpectFieldValue("firstname", "M");
    ExpectFieldValue("lastname", "");
    ExpectFieldValue("address1", "");
    ExpectFieldValue("address2", "");
    ExpectFieldValue("city", "");
    ExpectFieldValue("state", "");
    ExpectFieldValue("zip", "");
    ExpectFieldValue("country", "");
    ExpectFieldValue("phone", "");

    LOG(WARNING) << "Simulating Return press to fill the form.";
    SendKeyToPopupAndWait(ui::VKEY_RETURN);

    ExpectFilledTestForm();
  }
