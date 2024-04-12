void GLES2DecoderImpl::OnOutOfMemoryError() {
  if (lose_context_when_out_of_memory_) {
    group_->LoseContexts(GL_UNKNOWN_CONTEXT_RESET_ARB);
  }
}
