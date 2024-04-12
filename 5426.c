bool HWNDMessageHandler::IsActive() const {
  return GetActiveWindow() == hwnd();
}
