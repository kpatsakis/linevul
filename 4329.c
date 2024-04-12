void HTMLInputElement::ResetImpl() {
  if (input_type_->GetValueMode() == ValueMode::kValue) {
    SetNonDirtyValue(DefaultValue());
    SetNeedsValidityCheck();
  } else if (input_type_->GetValueMode() == ValueMode::kFilename) {
    SetNonDirtyValue(String());
    SetNeedsValidityCheck();
  }

  setChecked(hasAttribute(checkedAttr));
  dirty_checkedness_ = false;
}
