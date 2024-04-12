void RenderFrameHostImpl::OnSetNeedsOcclusionTracking(bool needs_tracking) {
  RenderFrameProxyHost* proxy =
      frame_tree_node()->render_manager()->GetProxyToParent();
  if (!proxy) {
    bad_message::ReceivedBadMessage(GetProcess(),
                                    bad_message::RFH_NO_PROXY_TO_PARENT);
    return;
  }

  proxy->Send(new FrameMsg_SetNeedsOcclusionTracking(proxy->GetRoutingID(),
                                                     needs_tracking));
}
