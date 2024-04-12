int BrowserWindowGtk::GetVerticalOffset() {
  return (IsMaximized() || (!UseCustomFrame())) ?
      -kCustomFrameBackgroundVerticalOffset : 0;
}
