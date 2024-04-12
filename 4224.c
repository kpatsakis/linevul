void GLES2DecoderImpl::RenderbufferStorageMultisampleHelper(
    GLenum target,
    GLsizei samples,
    GLenum internal_format,
    GLsizei width,
    GLsizei height,
    ForcedMultisampleMode mode) {
  if (samples == 0) {
    api()->glRenderbufferStorageEXTFn(target, internal_format, width, height);
    return;
  }


  if (mode == kForceExtMultisampledRenderToTexture) {
    api()->glRenderbufferStorageMultisampleEXTFn(
        target, samples, internal_format, width, height);
  } else {
    api()->glRenderbufferStorageMultisampleFn(target, samples, internal_format,
                                              width, height);
  }
}
