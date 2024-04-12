bool GetWindowManagerName(std::string* wm_name) {
  DCHECK(wm_name);
  int wm_window = 0;
  if (!GetIntProperty(GetX11RootWindow(),
                      "_NET_SUPPORTING_WM_CHECK",
                      &wm_window)) {
    return false;
  }


  gdk_error_trap_push();
  int wm_window_property = 0;
  bool result = GetIntProperty(
      wm_window, "_NET_SUPPORTING_WM_CHECK", &wm_window_property);
  gdk_flush();
  bool got_error = gdk_error_trap_pop();
  if (got_error || !result || wm_window_property != wm_window)
    return false;

  gdk_error_trap_push();
  result = GetStringProperty(
      static_cast<XID>(wm_window), "_NET_WM_NAME", wm_name);
  gdk_flush();
  got_error = gdk_error_trap_pop();
  return !got_error && result;
}
