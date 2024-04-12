void AutoFillManager::FillFormField(const AutoFillProfile* profile,
                                    AutoFillType type,
                                    webkit_glue::FormField* field) {
  DCHECK(profile);
  DCHECK(field);

  if (type.subgroup() == AutoFillType::PHONE_NUMBER) {
    FillPhoneNumberField(profile, field);
  } else {
    if (field->form_control_type() == ASCIIToUTF16("select-one"))
      autofill::FillSelectControl(profile, type, field);
    else
      field->set_value(profile->GetFieldText(type));
  }
}
