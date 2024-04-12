void BackRenderbuffer::Destroy() {
  if (id_ != 0) {
    ScopedGLErrorSuppressor suppressor("BackRenderbuffer::Destroy",
                                       decoder_->error_state_.get());
    api()->glDeleteRenderbuffersEXTFn(1, &id_);
    id_ = 0;
  }
  memory_tracker_.TrackMemFree(bytes_allocated_);
  bytes_allocated_ = 0;
}
