error::Error GLES2DecoderImpl::HandleGetActiveUniformBlockiv(
    uint32 immediate_data_size, const void* cmd_data) {
  if (!unsafe_es3_apis_enabled())
    return error::kUnknownCommand;
  const gles2::cmds::GetActiveUniformBlockiv& c =
      *static_cast<const gles2::cmds::GetActiveUniformBlockiv*>(cmd_data);
  GLuint program_id = c.program;
  GLuint index = static_cast<GLuint>(c.index);
  GLenum pname = static_cast<GLenum>(c.pname);
  Program* program = GetProgramInfoNotShader(
      program_id, "glGetActiveUniformBlockiv");
  if (!program) {
    return error::kNoError;
  }
  GLuint service_id = program->service_id();
  GLint link_status = GL_FALSE;
  glGetProgramiv(service_id, GL_LINK_STATUS, &link_status);
  if (link_status != GL_TRUE) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION,
        "glGetActiveActiveUniformBlockiv", "program not linked");
    return error::kNoError;
  }
  LOCAL_COPY_REAL_GL_ERRORS_TO_WRAPPER("GetActiveUniformBlockiv");
  GLsizei num_values = 1;
  if (pname == GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES) {
    GLint num = 0;
    glGetActiveUniformBlockiv(
        service_id, index, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &num);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      LOCAL_SET_GL_ERROR(error, "GetActiveUniformBlockiv", "");
      return error::kNoError;
    }
    num_values = static_cast<GLsizei>(num);
  }
  typedef cmds::GetActiveUniformBlockiv::Result Result;
  Result* result = GetSharedMemoryAs<Result*>(
      c.params_shm_id, c.params_shm_offset, Result::ComputeSize(num_values));
  GLint* params = result ? result->GetData() : NULL;
  if (params == NULL) {
    return error::kOutOfBounds;
  }
  if (result->size != 0) {
    return error::kInvalidArguments;
  }
  glGetActiveUniformBlockiv(service_id, index, pname, params);
  GLenum error = glGetError();
  if (error == GL_NO_ERROR) {
    result->SetNumResults(num_values);
  } else {
    LOCAL_SET_GL_ERROR(error, "GetActiveUniformBlockiv", "");
  }
  return error::kNoError;
}
