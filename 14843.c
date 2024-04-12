void WebLocalFrameImpl::ReplaceSelection(const WebString& text) {
  GetFrame()->GetDocument()->UpdateStyleAndLayoutIgnorePendingStylesheets();

  GetFrame()->GetEditor().ReplaceSelection(text);
}
