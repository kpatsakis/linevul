error::Error GLES2DecoderImpl::HandleGetUniformuiv(
    uint32_t immediate_data_size,
    const volatile void* cmd_data) {
  if (!feature_info_->IsWebGL2OrES3Context())
    return error::kUnknownCommand;

  const volatile gles2::cmds::GetUniformuiv& c =
      *static_cast<const volatile gles2::cmds::GetUniformuiv*>(cmd_data);
  GLuint program = c.program;
  GLint fake_location = c.location;
  GLuint service_id;
  GLenum result_type;
  GLsizei result_size;
  GLint real_location = -1;
  Error error;
  cmds::GetUniformuiv::Result* result;
  if (GetUniformSetup<GLuint>(program, fake_location, c.params_shm_id,
                              c.params_shm_offset, &error, &real_location,
                              &service_id, &result, &result_type,
                              &result_size)) {
    api()->glGetUniformuivFn(service_id, real_location, result->GetData());
  }
  return error;
}
