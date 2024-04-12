bool GLES2DecoderPassthroughImpl::FlushErrors() {
  bool had_error = false;
  GLenum error = glGetError();
  while (error != GL_NO_ERROR) {
    errors_.insert(error);
    had_error = true;

    if (error == GL_OUT_OF_MEMORY && !WasContextLost() &&
        lose_context_when_out_of_memory_) {
      error::ContextLostReason other = error::kOutOfMemory;
      if (CheckResetStatus()) {
        other = error::kUnknown;
      } else {
        MarkContextLost(error::kOutOfMemory);
      }
      group_->LoseContexts(other);
      break;
    }

    error = glGetError();
  }
  return had_error;
}
