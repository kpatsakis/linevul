void LocalFrame::Navigate(const FrameLoadRequest& request) {
  loader_.StartNavigation(request);
}
