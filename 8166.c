error::Error GLES2DecoderImpl::HandleBindUniformLocationCHROMIUM(
    uint32 immediate_data_size, const cmds::BindUniformLocationCHROMIUM& c) {
  GLuint program = static_cast<GLuint>(c.program);
  GLint location = static_cast<GLint>(c.location);
  uint32 name_size = c.data_size;
  const char* name = GetSharedMemoryAs<const char*>(
      c.name_shm_id, c.name_shm_offset, name_size);
  if (name == NULL) {
    return error::kOutOfBounds;
  }
  std::string name_str(name, name_size);
  DoBindUniformLocationCHROMIUM(program, location, name_str.c_str());
  return error::kNoError;
}
