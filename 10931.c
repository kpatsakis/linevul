void WebContentsImpl::DidNavigateMainFramePreCommit(
    bool navigation_is_within_page) {
  if (navigation_is_within_page) {
    return;
  }
  if (IsFullscreenForCurrentTab(GetRenderViewHost()->GetWidget()))
    ExitFullscreen(false);
  DCHECK(!IsFullscreenForCurrentTab(GetRenderViewHost()->GetWidget()));
}
