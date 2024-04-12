bool WebContentsImpl::WasDiscarded() {
  return GetFrameTree()->root()->was_discarded();
}
