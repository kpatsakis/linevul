bool GLES2DecoderImpl::GetUniformSetup(GLuint program_id,
                                       GLint fake_location,
                                       uint32_t shm_id,
                                       uint32_t shm_offset,
                                       error::Error* error,
                                       GLint* real_location,
                                       GLuint* service_id,
                                       SizedResult<T>** result_pointer,
                                       GLenum* result_type,
                                       GLsizei* result_size) {
  DCHECK(error);
  DCHECK(service_id);
  DCHECK(result_pointer);
  DCHECK(result_type);
  DCHECK(result_size);
  DCHECK(real_location);
  *error = error::kNoError;
  SizedResult<T>* result;
  result = GetSharedMemoryAs<SizedResult<T>*>(
      shm_id, shm_offset, SizedResult<T>::ComputeSize(0));
  if (!result) {
    *error = error::kOutOfBounds;
    return false;
  }
  *result_pointer = result;
  result->SetNumResults(0);
  Program* program = GetProgramInfoNotShader(program_id, "glGetUniform");
  if (!program) {
    return false;
  }
  if (!program->IsValid()) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION, "glGetUniform", "program not linked");
    return false;
  }
  *service_id = program->service_id();
  GLint array_index = -1;
  const Program::UniformInfo* uniform_info =
      program->GetUniformInfoByFakeLocation(
          fake_location, real_location, &array_index);
  if (!uniform_info) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION, "glGetUniform", "unknown location");
    return false;
  }
  GLenum type = uniform_info->type;
  uint32_t num_elements = GLES2Util::GetElementCountForUniformType(type);
  if (num_elements == 0) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, "glGetUniform", "unknown type");
    return false;
  }
  result = GetSharedMemoryAs<SizedResult<T>*>(
      shm_id, shm_offset, SizedResult<T>::ComputeSize(num_elements));
  if (!result) {
    *error = error::kOutOfBounds;
    return false;
  }
  result->SetNumResults(num_elements);
  *result_size = num_elements * sizeof(T);
  *result_type = type;
  return true;
}
