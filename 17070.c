int LocalDOMWindow::innerWidth() const {
  if (!GetFrame())
    return 0;

  return AdjustForAbsoluteZoom::AdjustInt(GetViewportSize().Width(),
                                          GetFrame()->PageZoomFactor());
}
