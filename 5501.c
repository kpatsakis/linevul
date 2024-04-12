gfx::Rect SettingLevelBubbleDelegateView::GetAnchorRect() {
  gfx::Size view_size = GetPreferredSize();
  gfx::Rect monitor_area = gfx::Screen::GetMonitorAreaNearestWindow(NULL);
  return (gfx::Rect(
      monitor_area.x() + kBubbleXRatio * monitor_area.width(),
      monitor_area.bottom() - view_size.height() / 2 - kBubbleBottomGap, 0, 0));
}
