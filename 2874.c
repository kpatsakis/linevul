bool GLES2DecoderImpl::DoIsProgram(GLuint client_id) {
  const ProgramManager::ProgramInfo* program = GetProgramInfo(client_id);
  return program != NULL && !program->IsDeleted();
}
