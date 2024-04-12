void GLES2DecoderImpl::OnOutOfMemoryError() {
  if (lose_context_when_out_of_memory_ && !WasContextLost()) {
    error::ContextLostReason other = error::kOutOfMemory;
    if (CheckResetStatus()) {
      other = error::kUnknown;
    } else {
      MarkContextLost(error::kOutOfMemory);
    }
    group_->LoseContexts(other);
  }
}
