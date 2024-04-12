void AutofillManager::DisambiguateAddressUploadTypes(FormStructure* form,
                                                     size_t current_index) {

  ServerFieldTypeSet matching_types;
  size_t next_index = current_index + 1;
  if (next_index < form->field_count() &&
      form->field(next_index)->Type().GetStorableType() == ADDRESS_HOME_LINE2 &&
      form->field(next_index)->possible_types().count(EMPTY_TYPE)) {
    matching_types.insert(ADDRESS_HOME_LINE1);
  } else {
    matching_types.insert(ADDRESS_HOME_STREET_ADDRESS);
  }

  AutofillField* field = form->field(current_index);
  field->set_possible_types(matching_types);
}
