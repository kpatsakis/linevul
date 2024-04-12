void Compositor::SetAcceleratedWidget(gfx::AcceleratedWidget widget) {
  DCHECK(!widget_valid_);
  widget_ = widget;
  widget_valid_ = true;
  if (layer_tree_frame_sink_requested_) {
    context_factory_->CreateLayerTreeFrameSink(
        context_creation_weak_ptr_factory_.GetWeakPtr());
  }
}
