void GLES2DecoderImpl::RestoreStateForAttrib(GLuint attrib) {
  const VertexAttribManager::VertexAttribInfo* info =
      vertex_attrib_manager_->GetVertexAttribInfo(attrib);
  const void* ptr = reinterpret_cast<const void*>(info->offset());
  BufferManager::BufferInfo* buffer_info = info->buffer();
  glBindBuffer(GL_ARRAY_BUFFER, buffer_info ? buffer_info->service_id() : 0);
  glVertexAttribPointer(
      attrib, info->size(), info->type(), info->normalized(), info->gl_stride(),
      ptr);
  if (info->divisor())
    glVertexAttribDivisorANGLE(attrib, info->divisor());
  glBindBuffer(GL_ARRAY_BUFFER,
               bound_array_buffer_ ? bound_array_buffer_->service_id() : 0);

  if (attrib != 0 ||
      gfx::GetGLImplementation() == gfx::kGLImplementationEGLGLES2) {
    if (info->enabled()) {
      glEnableVertexAttribArray(attrib);
    } else {
      glDisableVertexAttribArray(attrib);
    }
  }
}
