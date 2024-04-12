void LayerTreeHostImpl::SetDebugState(
    const LayerTreeDebugState& new_debug_state) {
  if (LayerTreeDebugState::Equal(debug_state_, new_debug_state))
    return;

  debug_state_ = new_debug_state;
  UpdateTileManagerMemoryPolicy(ActualManagedMemoryPolicy());
  SetFullViewportDamage();
}
