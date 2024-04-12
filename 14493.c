void BrowserView::UpdateReloadStopState(bool is_loading, bool force) {
  toolbar_->reload_button()->ChangeMode(
      is_loading ? ReloadButton::MODE_STOP : ReloadButton::MODE_RELOAD, force);
}
