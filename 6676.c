void Browser::ContentsMouseEvent(
    TabContents* source, const gfx::Point& location, bool motion) {
  if (!GetStatusBubble())
    return;

  if (source == GetSelectedTabContents()) {
    GetStatusBubble()->MouseMoved(location, !motion);
    if (!motion)
      GetStatusBubble()->SetURL(GURL(), std::string());
  }
}
