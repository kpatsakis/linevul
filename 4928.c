error::Error GLES2DecoderPassthroughImpl::DoIsEnabled(GLenum cap,
                                                      uint32_t* result) {
  *result = api()->glIsEnabledFn(cap);
  return error::kNoError;
}
