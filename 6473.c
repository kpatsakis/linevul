GLES2Implementation::DeferErrorCallbacks::DeferErrorCallbacks(
    GLES2Implementation* gles2_implementation)
    : gles2_implementation_(gles2_implementation) {
  DCHECK_EQ(false, gles2_implementation_->deferring_error_callbacks_);
  gles2_implementation_->deferring_error_callbacks_ = true;
}
