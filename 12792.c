void RenderViewImpl::OnCSSInsertRequest(const string16& frame_xpath,
                                        const std::string& css) {
  WebFrame* frame = GetChildFrame(frame_xpath);
  if (!frame)
    return;

  frame->document().insertUserStyleSheet(
      WebString::fromUTF8(css),
      WebDocument::UserStyleAuthorLevel);
}
