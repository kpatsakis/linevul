LayerTreeHost::ReleaseCompositorFrameSink() {
  DCHECK(!visible_);

  DidLoseCompositorFrameSink();
  proxy_->ReleaseCompositorFrameSink();
  return std::move(current_compositor_frame_sink_);
}
