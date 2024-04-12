void InputMethodIBus::OnTextInputTypeChanged(const TextInputClient* client) {
  if (IsTextInputClientFocused(client)) {
    ResetContext();
    UpdateContextFocusState();
    if (previous_textinput_type_ != client->GetTextInputType())
      OnInputMethodChanged();
  }
  InputMethodBase::OnTextInputTypeChanged(client);
 }
