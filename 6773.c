WebKit::WebNode RenderViewImpl::GetFocusedNode() const {
  if (!webview())
    return WebNode();
  WebFrame* focused_frame = webview()->focusedFrame();
  if (focused_frame) {
    WebDocument doc = focused_frame->document();
    if (!doc.isNull())
      return doc.focusedNode();
  }

  return WebNode();
}
