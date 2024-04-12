void RenderFrameHostImpl::OnCreateChildFrame(
    int new_routing_id,
    service_manager::mojom::InterfaceProviderRequest
        new_interface_provider_provider_request,
    blink::WebTreeScopeType scope,
    const std::string& frame_name,
    const std::string& frame_unique_name,
    bool is_created_by_script,
    const base::UnguessableToken& devtools_frame_token,
    const blink::FramePolicy& frame_policy,
    const FrameOwnerProperties& frame_owner_properties) {
  DCHECK(!frame_unique_name.empty());
  DCHECK(new_interface_provider_provider_request.is_pending());

  if (!is_active() || !IsCurrent() || !render_frame_created_)
    return;

  frame_tree_->AddFrame(frame_tree_node_, GetProcess()->GetID(), new_routing_id,
                        std::move(new_interface_provider_provider_request),
                        scope, frame_name, frame_unique_name,
                        is_created_by_script, devtools_frame_token,
                        frame_policy, frame_owner_properties);
}
