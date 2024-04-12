CompositorImpl::CompositorImpl(CompositorClient* client,
                               gfx::NativeWindow root_window)
    : frame_sink_id_(AllocateFrameSinkId()),
      resource_manager_(root_window),
      window_(NULL),
      surface_handle_(gpu::kNullSurfaceHandle),
      client_(client),
      needs_animate_(false),
      pending_frames_(0U),
      layer_tree_frame_sink_request_pending_(false),
      lock_manager_(base::ThreadTaskRunnerHandle::Get()),
      enable_surface_synchronization_(
          features::IsSurfaceSynchronizationEnabled()),
      enable_viz_(
          base::FeatureList::IsEnabled(features::kVizDisplayCompositor)),
      weak_factory_(this) {
  DCHECK(client);

  SetRootWindow(root_window);

  display::Screen::GetScreen()->AddObserver(this);
}
