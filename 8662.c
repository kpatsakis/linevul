const AtomicString& LocalDOMWindow::name() const {
  if (!IsCurrentlyDisplayedInFrame())
    return g_null_atom;

  return GetFrame()->Tree().GetName();
}
