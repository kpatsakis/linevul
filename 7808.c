InputMethodIMM32::InputMethodIMM32(internal::InputMethodDelegate* delegate,
                                   HWND toplevel_window_handle)
    : InputMethodWin(delegate, toplevel_window_handle),
      enabled_(false), is_candidate_popup_open_(false),
      composing_window_handle_(NULL) {
  InputMethodWin::OnFocus();
}
