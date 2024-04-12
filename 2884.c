void HTMLInputElement::InitializeTypeInParsing() {
  DCHECK(parsing_in_progress_);
  DCHECK(!input_type_);
  DCHECK(!input_type_view_);

  const AtomicString& new_type_name =
      InputType::NormalizeTypeName(FastGetAttribute(typeAttr));
  input_type_ = InputType::Create(*this, new_type_name);
  input_type_view_ = input_type_->CreateView();
  String default_value = FastGetAttribute(valueAttr);
  if (input_type_->GetValueMode() == ValueMode::kValue)
    non_attribute_value_ = SanitizeValue(default_value);
  has_been_password_field_ |= new_type_name == InputTypeNames::password;

  if (input_type_view_->NeedsShadowSubtree()) {
    CreateUserAgentShadowRoot();
    CreateShadowSubtree();
  }

  SetNeedsWillValidateCheck();

  if (!default_value.IsNull())
    input_type_->WarnIfValueIsInvalid(default_value);

  input_type_view_->UpdateView();
}
