void InputMethodIBus::OnDidChangeFocusedClient(TextInputClient* focused_before,
                                               TextInputClient* focused) {
  OnTextInputTypeChanged(focused);

  UpdateContextFocusState();
  OnCaretBoundsChanged(focused);
}
