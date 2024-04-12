error::Error GLES2DecoderPassthroughImpl::DoCreateShader(GLenum type,
                                                         GLuint client_id) {
  return CreateHelper(client_id, &resources_->shader_id_map,
                      [this, type]() { return api()->glCreateShaderFn(type); });
}
