bool Browser::IsFullscreenForTabOrPending(
    const WebContents* web_contents) const {
  return fullscreen_controller_->IsFullscreenForTabOrPending(web_contents);
}
