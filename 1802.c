void LayerTreeHost::SetVisible(bool visible) {
  if (visible_ == visible)
    return;
  visible_ = visible;
  proxy_->SetVisible(visible);
}
