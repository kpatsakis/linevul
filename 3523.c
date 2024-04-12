views::Combobox* AutofillDialogViews::ComboboxForType(
    ServerFieldType type) {
  for (DetailGroupMap::iterator iter = detail_groups_.begin();
       iter != detail_groups_.end(); ++iter) {
    const DetailsGroup& group = iter->second;
    if (!delegate_->SectionIsActive(group.section))
      continue;

    ComboboxMap::const_iterator combo_mapping = group.comboboxes.find(type);
    if (combo_mapping != group.comboboxes.end())
      return combo_mapping->second;
  }

  return NULL;
}
