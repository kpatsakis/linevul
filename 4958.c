void InterstitialPageImpl::Disable() {
  enabled_ = false;

  static_cast<InterstitialPageNavigatorImpl*>(frame_tree_->root()->navigator())
      ->Disable();
}
