void GLES2DecoderImpl::DeleteBuffersHelper(
    GLsizei n, const GLuint* client_ids) {
  for (GLsizei ii = 0; ii < n; ++ii) {
    Buffer* buffer = GetBuffer(client_ids[ii]);
    if (buffer && !buffer->IsDeleted()) {
      buffer->RemoveMappedRange();
      state_.vertex_attrib_manager->Unbind(buffer);
      if (state_.bound_array_buffer.get() == buffer) {
        state_.bound_array_buffer = NULL;
      }
      RemoveBuffer(client_ids[ii]);
    }
  }
}
