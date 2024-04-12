bool GLES2DecoderPassthroughImpl::CheckErrorCallbackState() {
  bool had_error_ = had_error_callback_;
  had_error_callback_ = false;
  if (had_error_) {
    FlushErrors();
  }
  return had_error_;
}
