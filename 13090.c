void LocalFrameClientImpl::DidStopLoading() {
  if (web_frame_->Client())
    web_frame_->Client()->DidStopLoading();
}
