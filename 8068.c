ui::AXTreeIDRegistry::AXTreeID RenderFrameHostImpl::GetAXTreeID() {
  return ui::AXTreeIDRegistry::GetInstance()->GetOrCreateAXTreeID(
      GetProcess()->GetID(), routing_id_);
}
