void GLES2DecoderImpl::DoUniform1i(GLint fake_location, GLint v0) {
  GLenum type = 0;
  GLsizei count = 1;
  GLint real_location = -1;
  if (!PrepForSetUniformByLocation(fake_location,
                                   "glUniform1i",
                                   Program::kUniform1i,
                                   &real_location,
                                   &type,
                                   &count)) {
    return;
  }
  if (!state_.current_program->SetSamplers(
      state_.texture_units.size(), fake_location, 1, &v0)) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_VALUE, "glUniform1i", "texture unit out of range");
    return;
  }
  api()->glUniform1iFn(real_location, v0);
}
