error::Error GLES2DecoderPassthroughImpl::DoDepthMask(GLboolean flag) {
  api()->glDepthMaskFn(flag);
  return error::kNoError;
}
