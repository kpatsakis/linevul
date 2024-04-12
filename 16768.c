void LocalFrameClientImpl::DispatchDidChangeManifest() {
  if (web_frame_->Client())
    web_frame_->Client()->DidChangeManifest();
}
