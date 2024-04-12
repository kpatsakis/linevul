void LocalFrameClientImpl::DidDisplayContentWithCertificateErrors() {
  if (web_frame_->Client())
    web_frame_->Client()->DidDisplayContentWithCertificateErrors();
}
