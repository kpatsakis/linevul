void HWNDMessageHandler::SetSize(const gfx::Size& size) {
  SetWindowPos(hwnd(), NULL, 0, 0, size.width(), size.height(),
               SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
}
