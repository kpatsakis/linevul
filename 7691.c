error::Error GLES2DecoderPassthroughImpl::DoClearBufferfv(
    GLenum buffer,
    GLint drawbuffers,
    const volatile GLfloat* value) {
  api()->glClearBufferfvFn(buffer, drawbuffers,
                           const_cast<const GLfloat*>(value));
  return error::kNoError;
}
