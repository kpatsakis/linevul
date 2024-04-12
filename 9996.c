void BrowserWindowGtk::HandleKeyboardEvent(
    const NativeWebKeyboardEvent& event) {
  GdkEventKey* os_event = &event.os_event->key;

  if (!os_event || event.type != WebKit::WebInputEvent::RawKeyDown)
    return;

  int id = GetCustomCommandId(os_event);
  if (id != -1)
    chrome::ExecuteCommand(browser_.get(), id);
  else
    gtk_window_activate_key(window_, os_event);
}
