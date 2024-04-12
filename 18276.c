void RenderViewImpl::OnCopy() {
  if (!webview())
    return;

  base::AutoReset<bool> handling_select_range(&handling_select_range_, true);
  webview()->focusedFrame()->executeCommand(WebString::fromUTF8("Copy"),
                                            context_menu_node_);
}
