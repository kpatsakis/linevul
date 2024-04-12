bool ChromeClientImpl::AcceptsLoadDrops() const {
  return !web_view_->Client() || web_view_->Client()->AcceptsLoadDrops();
}
