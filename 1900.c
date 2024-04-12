void GLES2Implementation::VertexAttribIPointer(GLuint index,
                                               GLint size,
                                               GLenum type,
                                               GLsizei stride,
                                               const void* ptr) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glVertexAttribIPointer(" << index
                     << ", " << size << ", "
                     << GLES2Util::GetStringVertexAttribIType(type) << ", "
                     << stride << ", " << ptr << ")");
  if (!vertex_array_object_manager_->SetAttribPointer(
          bound_array_buffer_, index, size, type, GL_FALSE, stride, ptr,
          GL_TRUE)) {
    SetGLError(GL_INVALID_OPERATION, "glVertexAttribIPointer",
               "client side arrays are not allowed in vertex array objects.");
    return;
  }
  if (!support_client_side_arrays_ || bound_array_buffer_ != 0) {
    if (!ValidateOffset("glVertexAttribIPointer",
                        reinterpret_cast<GLintptr>(ptr))) {
      return;
    }
    helper_->VertexAttribIPointer(index, size, type, stride, ToGLuint(ptr));
  }
  CheckGLError();
}
