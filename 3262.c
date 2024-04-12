void RenderWidgetHostViewPort::GetDefaultScreenInfo(WebScreenInfo* results) {
  GdkWindow* gdk_window =
      gdk_display_get_default_group(gdk_display_get_default());
  GetScreenInfoFromNativeWindow(gdk_window, results);
}
