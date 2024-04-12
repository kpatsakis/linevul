bool WebGLRenderingContextBase::ValidateUniformMatrixParameters(
    const char* function_name,
    const WebGLUniformLocation* location,
    GLboolean transpose,
    void* v,
    GLsizei size,
    GLsizei required_min_size,
    GLuint src_offset,
    GLuint src_length) {
  DCHECK(size >= 0 && required_min_size > 0);
  if (!location)
    return false;
  if (location->Program() != current_program_) {
    SynthesizeGLError(GL_INVALID_OPERATION, function_name,
                      "location is not from current program");
    return false;
  }
  if (!v) {
    SynthesizeGLError(GL_INVALID_VALUE, function_name, "no array");
    return false;
  }
  if (transpose && !IsWebGL2OrHigher()) {
    SynthesizeGLError(GL_INVALID_VALUE, function_name, "transpose not FALSE");
    return false;
  }
  if (src_offset >= static_cast<GLuint>(size)) {
    SynthesizeGLError(GL_INVALID_VALUE, function_name, "invalid srcOffset");
    return false;
  }
  GLsizei actual_size = size - src_offset;
  if (src_length > 0) {
    if (src_length > static_cast<GLuint>(actual_size)) {
      SynthesizeGLError(GL_INVALID_VALUE, function_name,
                        "invalid srcOffset + srcLength");
      return false;
    }
    actual_size = src_length;
  }
  if (actual_size < required_min_size || (actual_size % required_min_size)) {
    SynthesizeGLError(GL_INVALID_VALUE, function_name, "invalid size");
    return false;
  }
  return true;
}
