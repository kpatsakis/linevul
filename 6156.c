  CompositorDependencies() : frame_sink_id_allocator(kDefaultClientId) {
    DCHECK_CURRENTLY_ON(BrowserThread::UI);

    bool enable_viz =
        base::FeatureList::IsEnabled(features::kVizDisplayCompositor);
    if (!enable_viz) {
      frame_sink_manager_impl = std::make_unique<viz::FrameSinkManagerImpl>(
          /*shared_bitmap_manager=*/nullptr);
      surface_utils::ConnectWithLocalFrameSinkManager(
          &host_frame_sink_manager, frame_sink_manager_impl.get());
    } else {
      CreateVizFrameSinkManager();
    }
  }
