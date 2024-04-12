void WebContentsImpl::WebContentsTreeNode::SetFocusedWebContents(
    WebContentsImpl* web_contents) {
  DCHECK(!outer_web_contents())
      << "Only the outermost WebContents tracks focus.";
  focused_web_contents_ = web_contents;
}
