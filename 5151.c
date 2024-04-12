error::Error GLES2DecoderImpl::HandleGetShaderInfoLog(
    uint32_t immediate_data_size,
    const volatile void* cmd_data) {
  const volatile gles2::cmds::GetShaderInfoLog& c =
      *static_cast<const volatile gles2::cmds::GetShaderInfoLog*>(cmd_data);
  GLuint shader_id = c.shader;
  uint32_t bucket_id = static_cast<uint32_t>(c.bucket_id);
  Bucket* bucket = CreateBucket(bucket_id);
  Shader* shader = GetShaderInfoNotProgram(shader_id, "glGetShaderInfoLog");
  if (!shader) {
    bucket->SetFromString("");
    return error::kNoError;
  }

  CompileShaderAndExitCommandProcessingEarly(shader);

  bucket->SetFromString(shader->log_info().c_str());
  return error::kNoError;
}
