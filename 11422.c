void HWNDMessageHandler::GetWindowPlacement(
    gfx::Rect* bounds,
    ui::WindowShowState* show_state) const {
  WINDOWPLACEMENT wp;
  wp.length = sizeof(wp);
  const bool succeeded = !!::GetWindowPlacement(hwnd(), &wp);
  DCHECK(succeeded);

  if (bounds != NULL) {
    if (wp.showCmd == SW_SHOWNORMAL) {
      const bool succeeded = GetWindowRect(hwnd(), &wp.rcNormalPosition) != 0;
      DCHECK(succeeded);

      *bounds = gfx::Rect(wp.rcNormalPosition);
    } else {
      MONITORINFO mi;
      mi.cbSize = sizeof(mi);
      const bool succeeded = base::win::GetMonitorInfoWrapper(
          MonitorFromWindow(hwnd(), MONITOR_DEFAULTTONEAREST), &mi) != 0;
      DCHECK(succeeded);

      *bounds = gfx::Rect(wp.rcNormalPosition);
      bounds->Offset(mi.rcWork.left - mi.rcMonitor.left,
                     mi.rcWork.top - mi.rcMonitor.top);
    }
  }

  if (show_state) {
    if (wp.showCmd == SW_SHOWMAXIMIZED)
      *show_state = ui::SHOW_STATE_MAXIMIZED;
    else if (wp.showCmd == SW_SHOWMINIMIZED)
      *show_state = ui::SHOW_STATE_MINIMIZED;
    else
      *show_state = ui::SHOW_STATE_NORMAL;
  }
}
