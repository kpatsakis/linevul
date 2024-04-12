error::Error GLES2DecoderImpl::HandleDeleteShader(
    uint32 immediate_data_size, const gles2::DeleteShader& c) {
  GLuint client_id = c.shader;
  if (client_id) {
    ShaderManager::ShaderInfo* info = GetShaderInfo(client_id);
    if (info) {
      if (!info->IsDeleted()) {
        glDeleteShader(info->service_id());
        shader_manager()->MarkAsDeleted(info);
      }
    } else {
      SetGLError(GL_INVALID_VALUE, "glDeleteShader: unknown shader");
    }
  }
  return error::kNoError;
}
