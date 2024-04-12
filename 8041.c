void TestingAutomationProvider::BuildSimpleWebKeyEvent(
    WebKit::WebInputEvent::Type type,
    int windows_key_code,
    NativeWebKeyboardEvent* event) {
  event->nativeKeyCode = 0;
  event->windowsKeyCode = windows_key_code;
  event->setKeyIdentifierFromWindowsKeyCode();
  event->type = type;
  event->modifiers = 0;
  event->isSystemKey = false;
  event->timeStampSeconds = base::Time::Now().ToDoubleT();
  event->skip_in_browser = true;
}
