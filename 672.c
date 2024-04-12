error::Error GLES2DecoderImpl::HandleGetActiveUniform(
    uint32 immediate_data_size, const cmds::GetActiveUniform& c) {
  GLuint program_id = c.program;
  GLuint index = c.index;
  uint32 name_bucket_id = c.name_bucket_id;
  typedef cmds::GetActiveUniform::Result Result;
  Result* result = GetSharedMemoryAs<Result*>(
      c.result_shm_id, c.result_shm_offset, sizeof(*result));
  if (!result) {
    return error::kOutOfBounds;
  }
  if (result->success != 0) {
    return error::kInvalidArguments;
  }
  Program* program = GetProgramInfoNotShader(
      program_id, "glGetActiveUniform");
  if (!program) {
    return error::kNoError;
  }
  const Program::UniformInfo* uniform_info =
      program->GetUniformInfo(index);
  if (!uniform_info) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_VALUE, "glGetActiveUniform", "index out of range");
    return error::kNoError;
  }
  result->success = 1;  // true.
  result->size = uniform_info->size;
  result->type = uniform_info->type;
  Bucket* bucket = CreateBucket(name_bucket_id);
  bucket->SetFromString(uniform_info->name.c_str());
  return error::kNoError;
}
