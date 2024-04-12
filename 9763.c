Frame* LocalFrameClientImpl::Opener() const {
  return ToCoreFrame(web_frame_->Opener());
}
