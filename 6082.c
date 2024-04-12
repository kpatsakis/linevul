void GLES2DecoderImpl::ReadBackBuffersIntoShadowCopies(
    base::flat_set<scoped_refptr<Buffer>> buffers_to_shadow_copy) {
  GLuint old_binding =
      state_.bound_array_buffer ? state_.bound_array_buffer->service_id() : 0;

  for (scoped_refptr<Buffer>& buffer : buffers_to_shadow_copy) {
    if (buffer->IsDeleted()) {
      continue;
    }
    void* shadow = nullptr;
    scoped_refptr<gpu::Buffer> gpu_buffer =
        buffer->TakeReadbackShadowAllocation(&shadow);
    if (!shadow) {
      continue;
    }

    if (buffer->GetMappedRange()) {
      continue;
    }

    api()->glBindBufferFn(GL_ARRAY_BUFFER, buffer->service_id());
    void* mapped = api()->glMapBufferRangeFn(GL_ARRAY_BUFFER, 0, buffer->size(),
                                             GL_MAP_READ_BIT);
    if (!mapped) {
      DLOG(ERROR) << "glMapBufferRange unexpectedly returned nullptr";
      MarkContextLost(error::kOutOfMemory);
      group_->LoseContexts(error::kUnknown);
      return;
    }
    memcpy(shadow, mapped, buffer->size());
    bool unmap_ok = api()->glUnmapBufferFn(GL_ARRAY_BUFFER);
    if (unmap_ok == GL_FALSE) {
      DLOG(ERROR) << "glUnmapBuffer unexpectedly returned GL_FALSE";
      MarkContextLost(error::kUnknown);
      group_->LoseContexts(error::kUnknown);
      return;
    }
  }

  api()->glBindBufferFn(GL_ARRAY_BUFFER, old_binding);
}
