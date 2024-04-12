error::Error GLES2DecoderPassthroughImpl::DoGetInternalformativ(GLenum target,
                                                                GLenum format,
                                                                GLenum pname,
                                                                GLsizei bufSize,
                                                                GLsizei* length,
                                                                GLint* params) {
  api()->glGetInternalformativRobustANGLEFn(target, format, pname, bufSize,
                                            length, params);
  return error::kNoError;
}
