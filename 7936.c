void WebMediaPlayerImpl::OnPause() {
  client_->RequestPause();
}
