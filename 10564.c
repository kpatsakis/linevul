void GLES2DecoderImpl::DoUniform4iv(
    GLint location, GLsizei count, const GLint* value) {
  GLenum type = 0;
  if (!PrepForSetUniformByLocation(location, "glUniform4iv", &type, &count)) {
    return;
  }
  glUniform4iv(location, count, value);
}
