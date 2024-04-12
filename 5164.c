int TestOpenInputDesktop() {
  bool is_interactive = false;
  if (IsInteractiveDesktop(&is_interactive) && is_interactive) {
    return SBOX_TEST_SUCCEEDED;
  }
  HDESK desk = ::OpenInputDesktop(0, FALSE, DESKTOP_CREATEWINDOW);
  if (desk) {
    ::CloseDesktop(desk);
    return SBOX_TEST_SUCCEEDED;
  }
  return SBOX_TEST_DENIED;
}
