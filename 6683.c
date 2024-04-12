void DownloadRequestLimiter::TabDownloadState::DidGetUserInteraction(
    const blink::WebInputEvent::Type type) {
  if (is_showing_prompt() ||
      type == blink::WebInputEvent::kGestureScrollBegin) {
    return;
  }

  bool promptable =
      PermissionRequestManager::FromWebContents(web_contents()) != nullptr;

  if ((status_ != DownloadRequestLimiter::ALLOW_ALL_DOWNLOADS) &&
      (!promptable ||
       (status_ != DownloadRequestLimiter::DOWNLOADS_NOT_ALLOWED))) {
    host_->Remove(this, web_contents());
  }
}
