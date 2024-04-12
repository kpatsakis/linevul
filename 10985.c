void InputMethodIMM32::OnDidChangeFocusedClient(TextInputClient* focused_before,
                                                TextInputClient* focused) {
  if (IsWindowFocused(focused)) {
    OnTextInputTypeChanged(focused);

    UpdateIMEState();

    OnCaretBoundsChanged(focused);
  }
}
