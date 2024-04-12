WebKit::WebUserMediaClient* RenderViewImpl::userMediaClient() {
  EnsureMediaStreamImpl();
  return media_stream_impl_;
}
