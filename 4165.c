bool WebContentsImpl::ShouldIgnoreInputEvents() {
  WebContentsImpl* web_contents = this;
  while (web_contents) {
    if (web_contents->ignore_input_events_)
      return true;
    web_contents = web_contents->GetOuterWebContents();
  }

  return false;
}
