bool LayerTreeHostImpl::InitializeRenderer(
    CompositorFrameSink* compositor_frame_sink) {
  TRACE_EVENT0("cc", "LayerTreeHostImpl::InitializeRenderer");

  ReleaseCompositorFrameSink();
  if (!compositor_frame_sink->BindToClient(this)) {
    return false;
  }

  if (!compositor_frame_sink->context_provider())
    SetMemoryPolicy(settings_.software_memory_policy);

  compositor_frame_sink_ = compositor_frame_sink;
  has_valid_compositor_frame_sink_ = true;
  resource_provider_ = base::MakeUnique<ResourceProvider>(
      compositor_frame_sink_->context_provider(),
      compositor_frame_sink_->shared_bitmap_manager(),
      compositor_frame_sink_->gpu_memory_buffer_manager(),
      task_runner_provider_->blocking_main_thread_task_runner(),
      settings_.renderer_settings.texture_id_allocation_chunk_size,
      compositor_frame_sink_->capabilities().delegated_sync_points_required,
      settings_.renderer_settings.use_gpu_memory_buffer_resources,
      settings_.enable_color_correct_rendering,
      settings_.renderer_settings.buffer_to_texture_target_map);

  UpdateGpuRasterizationStatus();

  active_tree_->set_needs_update_draw_properties();
  if (pending_tree_)
    pending_tree_->set_needs_update_draw_properties();

  CreateTileManagerResources();
  RecreateTileResources();

  client_->OnCanDrawStateChanged(CanDraw());
  SetFullViewportDamage();
  SetRequiresHighResToDraw();

  return true;
}
