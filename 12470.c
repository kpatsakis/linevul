void GLES2DecoderImpl::DoAttachShader(
    GLuint program_client_id, GLint shader_client_id) {
  Program* program = GetProgramInfoNotShader(
      program_client_id, "glAttachShader");
  if (!program) {
    return;
  }
  Shader* shader = GetShaderInfoNotProgram(shader_client_id, "glAttachShader");
  if (!shader) {
    return;
  }
  if (!program->AttachShader(shader_manager(), shader)) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glAttachShader",
        "can not attach more than one shader of the same type.");
    return;
  }
  glAttachShader(program->service_id(), shader->service_id());
}
