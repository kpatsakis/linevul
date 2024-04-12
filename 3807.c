error::Error GLES2DecoderPassthroughImpl::DoPolygonOffset(GLfloat factor,
                                                          GLfloat units) {
  api()->glPolygonOffsetFn(factor, units);
  return error::kNoError;
}
