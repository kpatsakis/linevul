GlobalFrameRoutingId RenderFrameHostImpl::GetGlobalFrameRoutingId() {
  return GlobalFrameRoutingId(GetProcess()->GetID(), GetRoutingID());
}
