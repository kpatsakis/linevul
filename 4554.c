RenderFrameHostImpl::BrowserPluginInstanceIDToAXTreeID(int instance_id) {
  RenderFrameHostImpl* guest = static_cast<RenderFrameHostImpl*>(
      delegate()->GetGuestByInstanceID(this, instance_id));
  if (!guest)
    return ui::AXTreeIDRegistry::kNoAXTreeID;

  guest->set_browser_plugin_embedder_ax_tree_id(GetAXTreeID());
  guest->UpdateAXTreeData();

  return guest->GetAXTreeID();
}
