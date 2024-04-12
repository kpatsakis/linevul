bool InputMethodWin::IsWindowFocused(const TextInputClient* client) const {
  if (!client)
    return false;
  HWND attached_window_handle = GetAttachedWindowHandle(client);
#if defined(USE_AURA)
  return attached_window_handle && GetActiveWindow() == attached_window_handle;
#else
  return attached_window_handle && GetFocus() == attached_window_handle;
#endif
}
