error::Error GLES2DecoderImpl::HandleDiscardBackbufferCHROMIUM(
    uint32 immediate_data_size, const cmds::DiscardBackbufferCHROMIUM& c) {
  if (surface_->DeferDraws())
    return error::kDeferCommandUntilLater;
  if (!surface_->SetBackbufferAllocation(false))
    return error::kLostContext;
  backbuffer_needs_clear_bits_ |= GL_COLOR_BUFFER_BIT;
  backbuffer_needs_clear_bits_ |= GL_DEPTH_BUFFER_BIT;
  backbuffer_needs_clear_bits_ |= GL_STENCIL_BUFFER_BIT;
  return error::kNoError;
}
