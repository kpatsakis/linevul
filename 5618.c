WGC3Denum WebGraphicsContext3DCommandBufferImpl::getError() {
  if (!synthetic_errors_.empty()) {
    std::vector<WGC3Denum>::iterator iter = synthetic_errors_.begin();
    WGC3Denum err = *iter;
    synthetic_errors_.erase(iter);
    return err;
  }

  return gl_->GetError();
}
