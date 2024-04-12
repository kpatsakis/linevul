bool PasswordAutofillAgent::WasFormStructureChanged(
    const FormStructureInfo& form_info) const {
  if (form_info.unique_renderer_id == FormData::kNotSetFormRendererId)
    return true;

  auto cached_form = forms_structure_cache_.find(form_info.unique_renderer_id);
  if (cached_form == forms_structure_cache_.end())
    return true;

  const FormStructureInfo& cached_form_info = cached_form->second;

  if (form_info.fields.size() != cached_form_info.fields.size())
    return true;

  for (size_t i = 0; i < form_info.fields.size(); ++i) {
    const FormFieldInfo& form_field = form_info.fields[i];
    const FormFieldInfo& cached_form_field = cached_form_info.fields[i];

    if (form_field.unique_renderer_id != cached_form_field.unique_renderer_id)
      return true;

    if (form_field.form_control_type != cached_form_field.form_control_type)
      return true;

    if (form_field.autocomplete_attribute !=
        cached_form_field.autocomplete_attribute) {
      return true;
    }

    if (form_field.is_focusable != cached_form_field.is_focusable)
      return true;
  }
  return false;
}
