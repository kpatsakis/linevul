bool GLES2DecoderImpl::InitializeSRGBConverter(
    const char* function_name) {
  if (!srgb_converter_.get()) {
    LOCAL_COPY_REAL_GL_ERRORS_TO_WRAPPER(function_name);
    srgb_converter_.reset(
        new SRGBConverter(feature_info_.get()));
    srgb_converter_->InitializeSRGBConverter(this);
    if (LOCAL_PEEK_GL_ERROR(function_name) != GL_NO_ERROR) {
      return false;
    }
  }
  return true;
}
