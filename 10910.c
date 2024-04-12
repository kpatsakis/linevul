error::Error GLES2DecoderPassthroughImpl::DoGetRequestableExtensionsCHROMIUM(
    const char** extensions) {
  *extensions = reinterpret_cast<const char*>(
      api()->glGetStringFn(GL_REQUESTABLE_EXTENSIONS_ANGLE));
  return error::kNoError;
}
