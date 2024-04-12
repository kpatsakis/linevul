void InputMethodLinuxX11::OnDidChangeFocusedClient(
    TextInputClient* focused_before,
    TextInputClient* focused) {
  input_method_context_->Reset();
  input_method_context_->OnTextInputTypeChanged(
      focused ? focused->GetTextInputType() : TEXT_INPUT_TYPE_NONE);

  InputMethodBase::OnDidChangeFocusedClient(focused_before, focused);
}
