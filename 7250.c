bool BrowserView::CanTriggerOnMouse() const {
  return !IsImmersiveModeEnabled();
}
