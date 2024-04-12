error::Error GLES2DecoderPassthroughImpl::DoGetTranslatedShaderSourceANGLE(
    GLuint shader,
    std::string* source) {
  CheckErrorCallbackState();
  GLuint service_id = GetShaderServiceID(shader, resources_);
  GLint translated_source_length = 0;
  api()->glGetShaderivFn(service_id, GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE,
                         &translated_source_length);
  if (CheckErrorCallbackState()) {
    return error::kNoError;
  }

  if (translated_source_length > 0) {
    std::vector<char> buffer(translated_source_length, 0);
    api()->glGetTranslatedShaderSourceANGLEFn(
        service_id, translated_source_length, nullptr, buffer.data());
    *source = std::string(buffer.data());
  }
  return error::kNoError;
}
