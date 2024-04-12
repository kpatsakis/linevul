void RenderFrameHostImpl::DidSelectPopupMenuItem(int selected_index) {
  Send(new FrameMsg_SelectPopupMenuItem(routing_id_, selected_index));
}
