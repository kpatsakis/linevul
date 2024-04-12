void RenderFrameImpl::DidClearWindowObject() {
  if (enabled_bindings_ & BINDINGS_POLICY_WEB_UI)
    WebUIExtension::Install(frame_);

  if (enabled_bindings_ & BINDINGS_POLICY_DOM_AUTOMATION)
    DomAutomationController::Install(this, frame_);

  if (enabled_bindings_ & BINDINGS_POLICY_STATS_COLLECTION)
    StatsCollectionController::Install(frame_);

  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();

  if (command_line.HasSwitch(cc::switches::kEnableGpuBenchmarking))
    GpuBenchmarking::Install(this);

  if (command_line.HasSwitch(switches::kEnableSkiaBenchmarking))
    SkiaBenchmarking::Install(frame_);

  for (auto& observer : render_view_->observers())
    observer.DidClearWindowObject(frame_);
  {
    SCOPED_UMA_HISTOGRAM_TIMER("RenderFrameObservers.DidClearWindowObject");
    for (auto& observer : observers_)
      observer.DidClearWindowObject();
  }
}
