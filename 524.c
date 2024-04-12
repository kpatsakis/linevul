void RenderFrameImpl::OnDelete() {
  frame_->ExecuteCommand(WebString::FromUTF8("Delete"));
}
