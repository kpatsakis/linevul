bool InputMethodWin::DispatchKeyEvent(
    const base::NativeEvent& native_key_event) {
  if (native_key_event.message == WM_CHAR) {
    BOOL handled;
    OnChar(native_key_event.hwnd, native_key_event.message,
           native_key_event.wParam, native_key_event.lParam, &handled);
    return !!handled;  // Don't send WM_CHAR for post event processing.
  }
  if (ui::IMM32Manager::IsRTLKeyboardLayoutInstalled() &&
      !IsTextInputTypeNone()) {
    const ui::KeyEvent key(native_key_event,
                           native_key_event.message == WM_CHAR);
    ui::KeyboardCode code = key.key_code();
    if (key.type() == ui::ET_KEY_PRESSED) {
      if (code == ui::VKEY_SHIFT) {
        base::i18n::TextDirection dir;
        if (ui::IMM32Manager::IsCtrlShiftPressed(&dir))
          pending_requested_direction_ = dir;
      } else if (code != ui::VKEY_CONTROL) {
        pending_requested_direction_ = base::i18n::UNKNOWN_DIRECTION;
      }
    } else if (key.type() == ui::ET_KEY_RELEASED &&
               (code == ui::VKEY_SHIFT || code == ui::VKEY_CONTROL) &&
               pending_requested_direction_ != base::i18n::UNKNOWN_DIRECTION) {
      GetTextInputClient()->ChangeTextDirectionAndLayoutAlignment(
          pending_requested_direction_);
      pending_requested_direction_ = base::i18n::UNKNOWN_DIRECTION;
    }
  }

  return DispatchKeyEventPostIME(native_key_event);
}
