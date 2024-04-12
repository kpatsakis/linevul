void Location::setPathname(LocalDOMWindow* current_window,
                           LocalDOMWindow* entered_window,
                           const String& pathname,
                           ExceptionState& exception_state) {
  KURL url = GetDocument()->Url();
  url.SetPath(pathname);
  SetLocation(url.GetString(), current_window, entered_window,
              &exception_state);
}
