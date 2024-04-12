double LocalDOMWindow::devicePixelRatio() const {
  if (!GetFrame())
    return 0.0;

  return GetFrame()->DevicePixelRatio();
}
