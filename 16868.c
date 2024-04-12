error::Error GLES2DecoderPassthroughImpl::DoBlendFunc(GLenum sfactor,
                                                      GLenum dfactor) {
  api()->glBlendFuncFn(sfactor, dfactor);
  return error::kNoError;
}
