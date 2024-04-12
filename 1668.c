void RenderViewImpl::OnGetRenderedText() {
  if (!webview())
    return;

  if (!webview()->MainFrame()->IsWebLocalFrame())
    return;

  static const size_t kMaximumMessageSize = 8 * 1024 * 1024;
  std::string text =
      WebFrameContentDumper::DumpWebViewAsText(webview(), kMaximumMessageSize)
          .Utf8();

  Send(new ViewMsg_GetRenderedTextCompleted(GetRoutingID(), text));
}
