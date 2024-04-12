void RenderFrameImpl::FrameFocused() {
  Send(new FrameHostMsg_FrameFocused(routing_id_));
}
