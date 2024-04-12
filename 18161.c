bool LayerTreeHostImpl::CanDraw() const {

  if (!compositor_frame_sink_) {
    TRACE_EVENT_INSTANT0("cc",
                         "LayerTreeHostImpl::CanDraw no CompositorFrameSink",
                         TRACE_EVENT_SCOPE_THREAD);
    return false;
  }

  if (active_tree_->LayerListIsEmpty()) {
    TRACE_EVENT_INSTANT0("cc", "LayerTreeHostImpl::CanDraw no root layer",
                         TRACE_EVENT_SCOPE_THREAD);
    return false;
  }

  if (resourceless_software_draw_)
    return true;

  if (DrawViewportSize().IsEmpty()) {
    TRACE_EVENT_INSTANT0("cc", "LayerTreeHostImpl::CanDraw empty viewport",
                         TRACE_EVENT_SCOPE_THREAD);
    return false;
  }
  if (active_tree_->ViewportSizeInvalid()) {
    TRACE_EVENT_INSTANT0(
        "cc", "LayerTreeHostImpl::CanDraw viewport size recently changed",
        TRACE_EVENT_SCOPE_THREAD);
    return false;
  }
  if (EvictedUIResourcesExist()) {
    TRACE_EVENT_INSTANT0(
        "cc", "LayerTreeHostImpl::CanDraw UI resources evicted not recreated",
        TRACE_EVENT_SCOPE_THREAD);
    return false;
  }
  return true;
}
