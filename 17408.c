bool Browser::PreHandleKeyboardEvent(content::WebContents* source,
                                     const NativeWebKeyboardEvent& event,
                                     bool* is_keyboard_shortcut) {
  if (exclusive_access_manager_->HandleUserKeyPress(event))
    return true;

  return window()->PreHandleKeyboardEvent(event, is_keyboard_shortcut);
}
