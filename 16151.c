void CompositorImpl::OnGpuChannelEstablished(
    scoped_refptr<gpu::GpuChannelHost> gpu_channel_host) {
  CompositorDependencies::Get().TryEstablishVizConnectionIfNeeded();

  if (!layer_tree_frame_sink_request_pending_)
    return;

  if (!gpu_channel_host) {
    HandlePendingLayerTreeFrameSinkRequest();
    return;
  }

  if (!host_->IsVisible()) {
    return;
  }

  DCHECK(window_);
  DCHECK_NE(surface_handle_, gpu::kNullSurfaceHandle);

  gpu::GpuChannelEstablishFactory* factory =
      BrowserMainLoop::GetInstance()->gpu_channel_establish_factory();

  int32_t stream_id = kGpuStreamIdDefault;
  gpu::SchedulingPriority stream_priority = kGpuStreamPriorityUI;

  constexpr bool support_locking = false;
  constexpr bool automatic_flushes = false;
  constexpr bool support_grcontext = true;
  display_color_space_ = display::Screen::GetScreen()
                             ->GetDisplayNearestWindow(root_window_)
                             .color_space();
  gpu::SurfaceHandle surface_handle =
      enable_viz_ ? gpu::kNullSurfaceHandle : surface_handle_;
  auto context_provider =
      base::MakeRefCounted<ws::ContextProviderCommandBuffer>(
          std::move(gpu_channel_host), factory->GetGpuMemoryBufferManager(),
          stream_id, stream_priority, surface_handle,
          GURL(std::string("chrome://gpu/CompositorImpl::") +
               std::string("CompositorContextProvider")),
          automatic_flushes, support_locking, support_grcontext,
          GetCompositorContextSharedMemoryLimits(root_window_),
          GetCompositorContextAttributes(display_color_space_,
                                         requires_alpha_channel_),
          ws::command_buffer_metrics::ContextType::BROWSER_COMPOSITOR);
  auto result = context_provider->BindToCurrentThread();
  if (result != gpu::ContextResult::kSuccess) {
    if (gpu::IsFatalOrSurfaceFailure(result))
      OnFatalOrSurfaceContextCreationFailure(result);
    HandlePendingLayerTreeFrameSinkRequest();
    return;
  }

  if (enable_viz_) {
    InitializeVizLayerTreeFrameSink(std::move(context_provider));
  } else {
    auto display_output_surface = std::make_unique<AndroidOutputSurface>(
        context_provider, base::BindRepeating(&CompositorImpl::DidSwapBuffers,
                                              base::Unretained(this)));
    InitializeDisplay(std::move(display_output_surface),
                      std::move(context_provider));
  }
}
