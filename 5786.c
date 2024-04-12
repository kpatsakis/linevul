void InputMethodBase::SetStickyFocusedTextInputClient(TextInputClient* client) {
  is_sticky_text_input_client_ = (client != NULL);
  SetFocusedTextInputClientInternal(client);
}
