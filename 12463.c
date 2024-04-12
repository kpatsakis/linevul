void AutocompletePopupViewGtk::InvalidateLine(size_t line) {
  GdkRectangle line_rect = GetRectForLine(
      line, GetWindowRect(window_->window).width()).ToGdkRectangle();
  gdk_window_invalidate_rect(window_->window, &line_rect, FALSE);
}
