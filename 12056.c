void RenderViewImpl::OnSetCompositionFromExistingText(
    int start, int end,
    const std::vector<WebKit::WebCompositionUnderline>& underlines) {
  if (!webview())
    return;
  DCHECK(!handling_ime_event_);
  handling_ime_event_ = true;
  webview()->setCompositionFromExistingText(start, end, underlines);
  handling_ime_event_ = false;
  UpdateTextInputState(DO_NOT_SHOW_IME);
}
