void RenderFrameImpl::CreateFrame(
    int routing_id,
    int parent_routing_id,
    int previous_sibling_routing_id,
    int proxy_routing_id,
    const FrameReplicationState& replicated_state,
    CompositorDependencies* compositor_deps,
    const FrameMsg_NewFrame_WidgetParams& widget_params) {
  blink::WebLocalFrame* web_frame;
  RenderFrameImpl* render_frame;
  if (proxy_routing_id == MSG_ROUTING_NONE) {
    RenderFrameProxy* parent_proxy =
        RenderFrameProxy::FromRoutingID(parent_routing_id);
    CHECK(parent_proxy);
    blink::WebRemoteFrame* parent_web_frame = parent_proxy->web_frame();

    blink::WebFrame* previous_sibling_web_frame = nullptr;
    RenderFrameProxy* previous_sibling_proxy =
        RenderFrameProxy::FromRoutingID(previous_sibling_routing_id);
    if (previous_sibling_proxy)
      previous_sibling_web_frame = previous_sibling_proxy->web_frame();

    render_frame =
        RenderFrameImpl::Create(parent_proxy->render_view(), routing_id);
    web_frame = parent_web_frame->createLocalChild(
        replicated_state.scope, WebString::fromUTF8(replicated_state.name),
        replicated_state.sandbox_flags, render_frame,
        previous_sibling_web_frame);
  } else {
    RenderFrameProxy* proxy =
        RenderFrameProxy::FromRoutingID(proxy_routing_id);
    CHECK(proxy);
    render_frame = RenderFrameImpl::Create(proxy->render_view(), routing_id);
    web_frame =
        blink::WebLocalFrame::create(replicated_state.scope, render_frame);
    render_frame->proxy_routing_id_ = proxy_routing_id;
    web_frame->initializeToReplaceRemoteFrame(
        proxy->web_frame(), WebString::fromUTF8(replicated_state.name),
        replicated_state.sandbox_flags);
  }
  render_frame->SetWebFrame(web_frame);
  CHECK_IMPLIES(parent_routing_id == MSG_ROUTING_NONE, !web_frame->parent());

  if (widget_params.routing_id != MSG_ROUTING_NONE) {
    CHECK(SiteIsolationPolicy::AreCrossProcessFramesPossible());
    render_frame->render_widget_ = RenderWidget::CreateForFrame(
        widget_params.routing_id, widget_params.surface_id,
        widget_params.hidden, render_frame->render_view_->screen_info(),
        compositor_deps, web_frame);
    render_frame->render_widget_->RegisterRenderFrame(render_frame);
  }

  render_frame->Initialize();
}
