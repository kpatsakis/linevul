String InputType::ResultForDialogSubmit() const {
  return GetElement().FastGetAttribute(valueAttr);
}
