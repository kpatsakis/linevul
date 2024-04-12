void DevToolsWindow::HandleKeyboardEvent(
    WebContents* source,
    const content::NativeWebKeyboardEvent& event) {
  if (event.windows_key_code == 0x08) {
    return;
  }
  BrowserWindow* inspected_window = GetInspectedBrowserWindow();
  if (inspected_window)
    inspected_window->HandleKeyboardEvent(event);
}
