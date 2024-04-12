void WebMediaPlayerImpl::OnBecameVisible() {
  needs_first_frame_ = !has_first_frame_;
  UpdatePlayState();
}
