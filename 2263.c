void WebLocalFrameImpl::SetName(const WebString& name) {
  GetFrame()->Tree().SetName(name, FrameTree::kReplicate);
}
