bool GLES2DecoderImpl::DoIsShader(GLuint client_id) {
  return GetShaderInfo(client_id) != NULL;
}
