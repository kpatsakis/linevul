bool GetWindowDesktop(XID window, int* desktop) {
  return GetIntProperty(window, "_NET_WM_DESKTOP", desktop);
}
