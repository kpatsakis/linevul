void HTMLInputElement::SetNonDirtyValue(const String& new_value) {
  setValue(new_value);
  has_dirty_value_ = false;
}
