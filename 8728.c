void GLES2DecoderImpl::DoBufferSubData(
  GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data) {
  buffer_manager()->ValidateAndDoBufferSubData(&state_, error_state_.get(),
                                               target, offset, size, data);
}
