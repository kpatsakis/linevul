void GLES2DecoderImpl::DoVertexAttribI4iv(GLuint index,
                                          const volatile GLint* v) {
  GLint t[4] = {v[0], v[1], v[2], v[3]};
  if (SetVertexAttribValue("glVertexAttribI4iv", index, t)) {
    state_.SetGenericVertexAttribBaseType(
        index, SHADER_VARIABLE_INT);
    api()->glVertexAttribI4ivFn(index, t);
  }
}
