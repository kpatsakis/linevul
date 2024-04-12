error::Error GLES2DecoderPassthroughImpl::DoPostSubBufferCHROMIUM(
    uint64_t swap_id,
    GLint x,
    GLint y,
    GLint width,
    GLint height,
    GLbitfield flags) {
  if (!surface_->SupportsPostSubBuffer()) {
    InsertError(GL_INVALID_OPERATION,
                "glPostSubBufferCHROMIUM is not supported for this surface.");
    return error::kNoError;
  }

  client()->OnSwapBuffers(swap_id, flags);
  return CheckSwapBuffersResult(
      surface_->PostSubBuffer(x, y, width, height, base::DoNothing()),
      "PostSubBuffer");
}
