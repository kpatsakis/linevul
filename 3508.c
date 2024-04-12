void LayerTreeHostImpl::NotifyReadyToDraw() {
  is_likely_to_require_a_draw_ = false;

  client_->NotifyReadyToDraw();
}
