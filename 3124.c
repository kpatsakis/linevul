DrawMode LayerTreeHostImpl::GetDrawMode() const {
  if (resourceless_software_draw_) {
    return DRAW_MODE_RESOURCELESS_SOFTWARE;
  } else if (compositor_frame_sink_->context_provider()) {
    return DRAW_MODE_HARDWARE;
  } else {
    return DRAW_MODE_SOFTWARE;
  }
}
