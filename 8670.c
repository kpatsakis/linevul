bool BrowserViewRenderer::IsVisible() const {
  return view_visible_ && (!attached_to_window_ || window_visible_);
}
