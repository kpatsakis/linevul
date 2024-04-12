void HWNDMessageHandler::OnWindowPosChanging(WINDOWPOS* window_pos) {
  if (ignore_window_pos_changes_) {
    if (!(window_pos->flags & ((IsVisible() ? SWP_HIDEWINDOW : SWP_SHOWWINDOW) |
        SWP_FRAMECHANGED)) &&
        (window_pos->flags & (SWP_NOZORDER | SWP_NOACTIVATE))) {
      window_pos->flags |= SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW;
      window_pos->flags &= ~(SWP_SHOWWINDOW | SWP_HIDEWINDOW);
    }
  } else if (!GetParent(hwnd())) {
    CRect window_rect;
    HMONITOR monitor;
    gfx::Rect monitor_rect, work_area;
    if (GetWindowRect(hwnd(), &window_rect) &&
        GetMonitorAndRects(window_rect, &monitor, &monitor_rect, &work_area)) {
      bool work_area_changed = (monitor_rect == last_monitor_rect_) &&
                               (work_area != last_work_area_);
      if (monitor && (monitor == last_monitor_) &&
          ((fullscreen_handler_->fullscreen() &&
            !fullscreen_handler_->metro_snap()) ||
            work_area_changed)) {
        gfx::Rect new_window_rect;
        if (fullscreen_handler_->fullscreen()) {
          new_window_rect = monitor_rect;
        } else if (IsMaximized()) {
          new_window_rect = work_area;
          int border_thickness = GetSystemMetrics(SM_CXSIZEFRAME);
          new_window_rect.Inset(-border_thickness, -border_thickness);
        } else {
          new_window_rect = gfx::Rect(window_rect);
          new_window_rect.AdjustToFit(work_area);
        }
        window_pos->x = new_window_rect.x();
        window_pos->y = new_window_rect.y();
        window_pos->cx = new_window_rect.width();
        window_pos->cy = new_window_rect.height();
        window_pos->flags &= ~(SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW);
        window_pos->flags |= SWP_NOCOPYBITS;

        ignore_window_pos_changes_ = true;
        base::MessageLoop::current()->PostTask(
            FROM_HERE,
            base::Bind(&HWNDMessageHandler::StopIgnoringPosChanges,
                       weak_factory_.GetWeakPtr()));
      }
      last_monitor_ = monitor;
      last_monitor_rect_ = monitor_rect;
      last_work_area_ = work_area;
    }
  }

  if (ScopedFullscreenVisibility::IsHiddenForFullscreen(hwnd())) {
    window_pos->flags &= ~SWP_SHOWWINDOW;
  }

  if (window_pos->flags & SWP_SHOWWINDOW)
    delegate_->HandleVisibilityChanging(true);
  else if (window_pos->flags & SWP_HIDEWINDOW)
    delegate_->HandleVisibilityChanging(false);

  SetMsgHandled(FALSE);
}
