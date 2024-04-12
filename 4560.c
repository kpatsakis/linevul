bool GLES2DecoderImpl::SetVertexAttribValue(
    const char* function_name, GLuint index, const GLfloat* value) {
  if (index >= state_.attrib_values.size()) {
    LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, function_name, "index out of range");
    return false;
  }
  Vec4& v = state_.attrib_values[index];
  v.v[0] = value[0];
  v.v[1] = value[1];
  v.v[2] = value[2];
  v.v[3] = value[3];
  return true;
}
