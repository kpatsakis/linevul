void RenderViewImpl::OnReplaceMisspelling(const string16& text) {
  if (!webview())
    return;

  WebFrame* frame = webview()->focusedFrame();
  if (!frame->hasSelection())
    return;

  frame->replaceMisspelledRange(text);
}
