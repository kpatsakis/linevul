void GLES2DecoderImpl::DoCompileShader(GLuint client_id) {
  TRACE_EVENT0("gpu", "GLES2DecoderImpl::DoCompileShader");
  Shader* shader = GetShaderInfoNotProgram(client_id, "glCompileShader");
  if (!shader) {
    return;
  }
  ShaderTranslator* translator = NULL;
  if (use_shader_translator_) {
    translator = shader->shader_type() == GL_VERTEX_SHADER ?
        vertex_translator_.get() : fragment_translator_.get();
  }

  program_manager()->DoCompileShader(
     shader,
     translator,
     feature_info_->feature_flags().angle_translated_shader_source ?
         ProgramManager::kANGLE : ProgramManager::kGL);
};
