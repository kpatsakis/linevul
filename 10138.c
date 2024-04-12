error::Error GLES2DecoderPassthroughImpl::DoVertexAttrib3fv(
    GLuint indx,
    const volatile GLfloat* values) {
  api()->glVertexAttrib3fvFn(indx, const_cast<const GLfloat*>(values));
  return error::kNoError;
}
