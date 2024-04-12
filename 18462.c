void GLES2DecoderImpl::DoUniform1iv(GLint fake_location,
                                    GLsizei count,
                                    const volatile GLint* values) {
  GLenum type = 0;
  GLint real_location = -1;
  if (!PrepForSetUniformByLocation(fake_location,
                                   "glUniform1iv",
                                   Program::kUniform1i,
                                   &real_location,
                                   &type,
                                   &count)) {
    return;
  }
  auto values_copy = std::make_unique<GLint[]>(count);
  GLint* safe_values = values_copy.get();
  std::copy(values, values + count, safe_values);
  if (type == GL_SAMPLER_2D || type == GL_SAMPLER_2D_RECT_ARB ||
      type == GL_SAMPLER_CUBE || type == GL_SAMPLER_EXTERNAL_OES) {
    if (!state_.current_program->SetSamplers(
            state_.texture_units.size(), fake_location, count, safe_values)) {
      LOCAL_SET_GL_ERROR(
          GL_INVALID_VALUE, "glUniform1iv", "texture unit out of range");
      return;
    }
  }
  api()->glUniform1ivFn(real_location, count, safe_values);
}
