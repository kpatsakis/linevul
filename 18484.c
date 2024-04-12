gfx::Rect GetWindowRect(GdkWindow* window) {
  gint width = gdk_window_get_width(window);
  gint height = gdk_window_get_height(window);
  return gfx::Rect(width, height);
}
