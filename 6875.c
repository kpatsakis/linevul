void BrowserWindowGtk::HideUnsupportedWindowFeatures() {
  if (!IsTabStripSupported())
    tabstrip_->Hide();

  if (!IsToolbarSupported())
    toolbar_->Hide();

}
