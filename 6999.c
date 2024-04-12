bool RenderFrameHostImpl::CreateRenderFrame(int proxy_routing_id,
                                            int opener_routing_id,
                                            int parent_routing_id,
                                            int previous_sibling_routing_id) {
  TRACE_EVENT0("navigation", "RenderFrameHostImpl::CreateRenderFrame");
  DCHECK(!IsRenderFrameLive()) << "Creating frame twice";

  if (!GetProcess()->Init())
    return false;

  DCHECK(GetProcess()->IsInitializedAndNotDead());

  service_manager::mojom::InterfaceProviderPtr interface_provider;
  BindInterfaceProviderRequest(mojo::MakeRequest(&interface_provider));

  blink::mojom::DocumentInterfaceBrokerPtrInfo
      document_interface_broker_content_info;
  blink::mojom::DocumentInterfaceBrokerPtrInfo
      document_interface_broker_blink_info;
  BindDocumentInterfaceBrokerRequest(
      mojo::MakeRequest(&document_interface_broker_content_info),
      mojo::MakeRequest(&document_interface_broker_blink_info));

  mojom::CreateFrameParamsPtr params = mojom::CreateFrameParams::New();
  params->interface_bundle = mojom::DocumentScopedInterfaceBundle::New(
      interface_provider.PassInterface(),
      std::move(document_interface_broker_content_info),
      std::move(document_interface_broker_blink_info));

  params->routing_id = routing_id_;
  params->proxy_routing_id = proxy_routing_id;
  params->opener_routing_id = opener_routing_id;
  params->parent_routing_id = parent_routing_id;
  params->previous_sibling_routing_id = previous_sibling_routing_id;
  params->replication_state = frame_tree_node()->current_replication_state();
  params->devtools_frame_token = frame_tree_node()->devtools_frame_token();

  params->replication_state.frame_policy =
      frame_tree_node()->pending_frame_policy();

  params->frame_owner_properties =
      FrameOwnerProperties(frame_tree_node()->frame_owner_properties());

  params->has_committed_real_load =
      frame_tree_node()->has_committed_real_load();

  params->widget_params = mojom::CreateFrameWidgetParams::New();
  if (render_widget_host_) {
    params->widget_params->routing_id = render_widget_host_->GetRoutingID();
    params->widget_params->hidden = render_widget_host_->is_hidden();
  } else {
    params->widget_params->routing_id = MSG_ROUTING_NONE;
    params->widget_params->hidden = true;
  }

  GetProcess()->GetRendererInterface()->CreateFrame(std::move(params));

  if (parent_routing_id != MSG_ROUTING_NONE && render_widget_host_) {
    RenderWidgetHostView* rwhv =
        RenderWidgetHostViewChildFrame::Create(render_widget_host_);
    rwhv->Hide();
  }

  if (proxy_routing_id != MSG_ROUTING_NONE) {
    RenderFrameProxyHost* proxy = RenderFrameProxyHost::FromID(
        GetProcess()->GetID(), proxy_routing_id);
    proxy->set_render_frame_proxy_created(true);
  }

  SetRenderFrameCreated(true);

  return true;
}
