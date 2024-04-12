void GLES2DecoderImpl::DoSetReadbackBufferShadowAllocationINTERNAL(
    GLuint buffer_id,
    GLuint shm_id,
    GLuint shm_offset,
    GLuint size) {
  static const char kFunctionName[] = "glSetBufferShadowAllocationINTERNAL";
  scoped_refptr<Buffer> buffer = buffer_manager()->GetBuffer(buffer_id);
  if (!buffer) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, kFunctionName, "unknown buffer");
    return;
  }
  if (static_cast<GLsizeiptr>(size) != buffer->size()) {
    MarkContextLost(error::kGuilty);
    group_->LoseContexts(error::kUnknown);
    return;
  }

  scoped_refptr<gpu::Buffer> shm = GetSharedMemoryBuffer(shm_id);
  buffer->SetReadbackShadowAllocation(shm, shm_offset);
  writes_submitted_but_not_completed_.insert(buffer);
}
