void SelectRightNameType(const ServerFieldTypeSet& old_types,
                         ServerFieldTypeSet* new_types,
                         bool is_credit_card) {
  ServerFieldTypeSet upload_types;
  if (old_types.count(NAME_FIRST) && old_types.count(CREDIT_CARD_NAME_FIRST)) {
    if (is_credit_card) {
      new_types->insert(CREDIT_CARD_NAME_FIRST);
    } else {
      new_types->insert(NAME_FIRST);
    }
  } else if (old_types.count(NAME_LAST) &&
             old_types.count(CREDIT_CARD_NAME_LAST)) {
    if (is_credit_card) {
      new_types->insert(CREDIT_CARD_NAME_LAST);
    } else {
      new_types->insert(NAME_LAST);
    }
  } else if (old_types.count(NAME_FULL) &&
             old_types.count(CREDIT_CARD_NAME_FULL)) {
    if (is_credit_card) {
      new_types->insert(CREDIT_CARD_NAME_FULL);
    } else {
      new_types->insert(NAME_FULL);
    }
  } else {
    *new_types = old_types;
  }
}
