bool LayerTreeHostImpl::IsActivelyScrolling() const {
  if (!CurrentlyScrollingNode())
    return false;
  if (settings_.ignore_root_layer_flings && IsCurrentlyScrollingViewport())
    return false;
  return did_lock_scrolling_layer_;
}
