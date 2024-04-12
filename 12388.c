void HWNDMessageHandler::NotifyOwnedWindowsParentClosing() {
  FindOwnedWindowsData data;
  data.window = hwnd();
  EnumThreadWindows(GetCurrentThreadId(), FindOwnedWindowsCallback,
                    reinterpret_cast<LPARAM>(&data));
  for (size_t i = 0; i < data.owned_widgets.size(); ++i)
    data.owned_widgets[i]->OnOwnerClosing();
}
