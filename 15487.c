void GLES2Implementation::DeleteSamplersStub(GLsizei n,
                                             const GLuint* samplers) {
  helper_->DeleteSamplersImmediate(n, samplers);
}
