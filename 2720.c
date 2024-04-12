WebContentsImpl* WebContentsImpl::GetFocusedWebContents() {
  return GetOutermostWebContents()->node_.focused_web_contents();
}
