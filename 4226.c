void GLES2DecoderImpl::DeleteBuffersHelper(GLsizei n,
                                           const volatile GLuint* client_ids) {
  for (GLsizei ii = 0; ii < n; ++ii) {
    GLuint client_id = client_ids[ii];
    Buffer* buffer = GetBuffer(client_id);
    if (buffer && !buffer->IsDeleted()) {
      if (buffer->GetMappedRange()) {
        GLenum target = buffer->initial_target();
        Buffer* currently_bound =
            buffer_manager()->GetBufferInfoForTarget(&state_, target);
        if (currently_bound != buffer) {
          api()->glBindBufferFn(target, buffer->service_id());
        }
        UnmapBufferHelper(buffer, target);
        if (currently_bound != buffer) {
          api()->glBindBufferFn(
              target, currently_bound ? currently_bound->service_id() : 0);
        }
      }
      state_.RemoveBoundBuffer(buffer);
      buffer_manager()->RemoveBuffer(client_id);
    }
  }
}
