void GLES2DecoderImpl::DoVertexAttribI4i(
    GLuint index, GLint v0, GLint v1, GLint v2, GLint v3) {
  GLint v[4] = { v0, v1, v2, v3 };
  if (SetVertexAttribValue("glVertexAttribI4i", index, v)) {
    state_.SetGenericVertexAttribBaseType(
        index, SHADER_VARIABLE_INT);
    api()->glVertexAttribI4iFn(index, v0, v1, v2, v3);
  }
}
