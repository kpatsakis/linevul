void LayerTreeHostImpl::ScrollOffsetAnimationFinished() {
  ScrollStateData scroll_state_data;
  ScrollState scroll_state(scroll_state_data);
  ScrollEnd(&scroll_state);
}
