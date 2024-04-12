void RenderFrameHostImpl::OnRequestOverlayRoutingToken() {
  GetOverlayRoutingToken();

  Send(new FrameMsg_SetOverlayRoutingToken(routing_id_,
                                           *overlay_routing_token_));
}
