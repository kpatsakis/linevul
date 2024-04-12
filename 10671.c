void CompositorImpl::DidInitializeLayerTreeFrameSink() {
  layer_tree_frame_sink_request_pending_ = false;
  has_layer_tree_frame_sink_ = true;
  for (auto& frame_sink_id : pending_child_frame_sink_ids_)
    AddChildFrameSink(frame_sink_id);

  pending_child_frame_sink_ids_.clear();
}
