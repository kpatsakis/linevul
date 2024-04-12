void AutofillDialogViews::SetIconsForSection(DialogSection section) {
  FieldValueMap user_input;
  GetUserInput(section, &user_input);
  FieldIconMap field_icons = delegate_->IconsForFields(user_input);
  TextfieldMap* textfields = &GroupForSection(section)->textfields;
  for (TextfieldMap::const_iterator textfield_it = textfields->begin();
       textfield_it != textfields->end();
       ++textfield_it) {
    ServerFieldType field_type = textfield_it->first;
    FieldIconMap::const_iterator field_icon_it = field_icons.find(field_type);
    ExpandingTextfield* textfield = textfield_it->second;
    if (field_icon_it != field_icons.end())
      textfield->SetIcon(field_icon_it->second);
    else
      textfield->SetTooltipIcon(delegate_->TooltipForField(field_type));
  }
}
