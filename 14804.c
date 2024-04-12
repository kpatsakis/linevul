bool GLES2DecoderImpl::ValidateCompressedTexDimensions(
    const char* function_name, GLenum target, GLint level,
    GLsizei width, GLsizei height, GLsizei depth, GLenum format) {
  const char* error_message = "";
  if (!::gpu::gles2::ValidateCompressedTexDimensions(
          target, level, width, height, depth, format,
          feature_info_->IsWebGLContext(), &error_message)) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name, error_message);
    return false;
  }
  return true;
}
