bool GLES2DecoderImpl::DoIsShader(GLuint client_id) {
  const ShaderManager::ShaderInfo* shader = GetShaderInfo(client_id);
  return shader != NULL && !shader->IsDeleted();
}
