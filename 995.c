error::Error GLES2DecoderPassthroughImpl::DoUniform2i(GLint location,
                                                      GLint x,
                                                      GLint y) {
  api()->glUniform2iFn(location, x, y);
  return error::kNoError;
}
