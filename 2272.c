void BaseAudioContext::ReleaseActiveSourceNodes() {
  DCHECK(IsMainThread());
  for (auto& source_node : active_source_nodes_)
    source_node->Handler().BreakConnection();

  active_source_nodes_.clear();
}
