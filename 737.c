void CompositorImpl::AddChildFrameSink(const viz::FrameSinkId& frame_sink_id) {
  if (has_layer_tree_frame_sink_) {
    GetHostFrameSinkManager()->RegisterFrameSinkHierarchy(frame_sink_id_,
                                                          frame_sink_id);
  } else {
    pending_child_frame_sink_ids_.insert(frame_sink_id);
  }
}
