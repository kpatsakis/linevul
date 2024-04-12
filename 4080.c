void RenderFrameImpl::Initialize() {
  is_main_frame_ = !frame_->Parent();

  GetLocalRootRenderWidget()->RegisterRenderFrame(this);

  RenderFrameImpl* parent_frame =
      RenderFrameImpl::FromWebFrame(frame_->Parent());
  if (parent_frame) {
    previews_state_ = parent_frame->GetPreviewsState();
    effective_connection_type_ = parent_frame->GetEffectiveConnectionType();
  }

  bool is_tracing_rail = false;
  bool is_tracing_navigation = false;
  TRACE_EVENT_CATEGORY_GROUP_ENABLED("navigation", &is_tracing_navigation);
  TRACE_EVENT_CATEGORY_GROUP_ENABLED("rail", &is_tracing_rail);
  if (is_tracing_rail || is_tracing_navigation) {
    int parent_id = RenderFrame::GetRoutingIdForWebFrame(frame_->Parent());
    TRACE_EVENT2("navigation,rail", "RenderFrameImpl::Initialize",
                 "id", routing_id_,
                 "parent", parent_id);
  }

  if (auto* thread = RenderThreadImpl::current()) {
    if (auto* controller = thread->low_memory_mode_controller())
      controller->OnFrameCreated(IsMainFrame());
  }

#if BUILDFLAG(ENABLE_PLUGINS)
  new PepperBrowserConnection(this);
#endif

  RegisterMojoInterfaces();

  GetContentClient()->renderer()->RenderFrameCreated(this);

  if (auto* factory = AudioOutputIPCFactory::get())
    factory->RegisterRemoteFactory(GetRoutingID(), GetRemoteInterfaces());

  AudioRendererSinkCache::ObserveFrame(this);

  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (command_line.HasSwitch(switches::kDomAutomationController))
    enabled_bindings_ |= BINDINGS_POLICY_DOM_AUTOMATION;
  if (command_line.HasSwitch(switches::kStatsCollectionController))
    enabled_bindings_ |= BINDINGS_POLICY_STATS_COLLECTION;
  if (base::FeatureList::IsEnabled(network::features::kNetworkService))
    frame_request_blocker_ = base::MakeRefCounted<FrameRequestBlocker>();

  RenderThread::Get()->AddRoute(routing_id_, this);
}
