void RenderFrameHostImpl::UpdateAccessibilityMode() {
  int accessibility_mode_raw = delegate_->GetAccessibilityMode().mode();
  Send(new FrameMsg_SetAccessibilityMode(routing_id_, accessibility_mode_raw));
}
