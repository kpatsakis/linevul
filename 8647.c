void RenderFrameImpl::OnSelectAll() {
  AutoResetMember<bool> handling_select_range(
      this, &RenderFrameImpl::handling_select_range_, true);
  frame_->ExecuteCommand(WebString::FromUTF8("SelectAll"));
}
