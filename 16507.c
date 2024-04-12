error::Error GLES2DecoderImpl::HandleBindAttribLocation(
    uint32 immediate_data_size, const gles2::BindAttribLocation& c) {
  GLuint program = static_cast<GLuint>(c.program);
  GLuint index = static_cast<GLuint>(c.index);
  uint32 name_size = c.data_size;
  const char* name = GetSharedMemoryAs<const char*>(
      c.name_shm_id, c.name_shm_offset, name_size);
  if (name == NULL) {
    return error::kOutOfBounds;
  }
  String name_str(name, name_size);
  DoBindAttribLocation(program, index, name_str.c_str());
  return error::kNoError;
}
