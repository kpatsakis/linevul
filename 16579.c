void LayerTreeHostImpl::BeginCommit() {
  TRACE_EVENT0("cc", "LayerTreeHostImpl::BeginCommit");

  if (compositor_frame_sink_)
    compositor_frame_sink_->ForceReclaimResources();

  if (!CommitToActiveTree())
    CreatePendingTree();
}
