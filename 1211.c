RenderFrameHostImpl::RenderFrameHostImpl(SiteInstance* site_instance,
                                         RenderViewHostImpl* render_view_host,
                                         RenderFrameHostDelegate* delegate,
                                         RenderWidgetHostDelegate* rwh_delegate,
                                         FrameTree* frame_tree,
                                         FrameTreeNode* frame_tree_node,
                                         int32_t routing_id,
                                         int32_t widget_routing_id,
                                         bool hidden,
                                         bool renderer_initiated_creation)
    : render_view_host_(render_view_host),
      delegate_(delegate),
      site_instance_(static_cast<SiteInstanceImpl*>(site_instance)),
      process_(site_instance->GetProcess()),
      frame_tree_(frame_tree),
      frame_tree_node_(frame_tree_node),
      parent_(nullptr),
      render_widget_host_(nullptr),
      routing_id_(routing_id),
      is_waiting_for_swapout_ack_(false),
      render_frame_created_(false),
      is_waiting_for_beforeunload_ack_(false),
      unload_ack_is_for_navigation_(false),
      was_discarded_(false),
      is_loading_(false),
      pending_commit_(false),
      nav_entry_id_(0),
      accessibility_reset_token_(0),
      accessibility_reset_count_(0),
      browser_plugin_embedder_ax_tree_id_(ui::AXTreeIDRegistry::kNoAXTreeID),
      no_create_browser_accessibility_manager_for_testing_(false),
      web_ui_type_(WebUI::kNoWebUI),
      pending_web_ui_type_(WebUI::kNoWebUI),
      should_reuse_web_ui_(false),
      has_selection_(false),
      is_audible_(false),
      last_navigation_previews_state_(PREVIEWS_UNSPECIFIED),
      frame_host_associated_binding_(this),
      waiting_for_init_(renderer_initiated_creation),
      has_focused_editable_element_(false),
      active_sandbox_flags_(blink::WebSandboxFlags::kNone),
      document_scoped_interface_provider_binding_(this),
      keep_alive_timeout_(base::TimeDelta::FromSeconds(30)),
      weak_ptr_factory_(this) {
  frame_tree_->AddRenderViewHostRef(render_view_host_);
  GetProcess()->AddRoute(routing_id_, this);
  g_routing_id_frame_map.Get().insert(std::make_pair(
      RenderFrameHostID(GetProcess()->GetID(), routing_id_),
      this));
  site_instance_->AddObserver(this);
  GetSiteInstance()->IncrementActiveFrameCount();

  if (frame_tree_node_->parent()) {
    parent_ = frame_tree_node_->parent()->current_frame_host();

    if (parent_->GetEnabledBindings())
      enabled_bindings_ = parent_->GetEnabledBindings();

    set_nav_entry_id(
        frame_tree_node_->parent()->current_frame_host()->nav_entry_id());
  }

  SetUpMojoIfNeeded();

  swapout_event_monitor_timeout_.reset(new TimeoutMonitor(base::Bind(
      &RenderFrameHostImpl::OnSwappedOut, weak_ptr_factory_.GetWeakPtr())));
  beforeunload_timeout_.reset(
      new TimeoutMonitor(base::Bind(&RenderFrameHostImpl::BeforeUnloadTimeout,
                                    weak_ptr_factory_.GetWeakPtr())));

  if (widget_routing_id != MSG_ROUTING_NONE) {
    mojom::WidgetPtr widget;
    GetRemoteInterfaces()->GetInterface(&widget);

    render_widget_host_ =
        RenderWidgetHostImpl::FromID(GetProcess()->GetID(), widget_routing_id);

    mojom::WidgetInputHandlerAssociatedPtr widget_handler;
    mojom::WidgetInputHandlerHostRequest host_request;
    if (frame_input_handler_) {
      mojom::WidgetInputHandlerHostPtr host;
      host_request = mojo::MakeRequest(&host);
      frame_input_handler_->GetWidgetInputHandler(
          mojo::MakeRequest(&widget_handler), std::move(host));
    }
    if (!render_widget_host_) {
      DCHECK(frame_tree_node->parent());
      render_widget_host_ = RenderWidgetHostFactory::Create(
          rwh_delegate, GetProcess(), widget_routing_id, std::move(widget),
          hidden);
      render_widget_host_->set_owned_by_render_frame_host(true);
    } else {
      DCHECK(!render_widget_host_->owned_by_render_frame_host());
      render_widget_host_->SetWidget(std::move(widget));
    }
    render_widget_host_->SetFrameDepth(frame_tree_node_->depth());
    render_widget_host_->SetWidgetInputHandler(std::move(widget_handler),
                                               std::move(host_request));
    render_widget_host_->input_router()->SetFrameTreeNodeId(
        frame_tree_node_->frame_tree_node_id());
  }
  ResetFeaturePolicy();

  ax_tree_id_ = ui::AXTreeIDRegistry::GetInstance()->GetOrCreateAXTreeID(
      GetProcess()->GetID(), routing_id_);

  FrameTreeNode* frame_owner = frame_tree_node_->parent()
                                   ? frame_tree_node_->parent()
                                   : frame_tree_node_->opener();
  if (frame_owner)
    CSPContext::SetSelf(frame_owner->current_origin());
}
