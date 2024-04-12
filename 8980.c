bool GLES2DecoderImpl::ValidateUniformBlockBackings(const char* func_name) {
  DCHECK(feature_info_->IsWebGL2OrES3Context());
  if (!state_.current_program.get())
    return true;
  int32_t max_index = -1;
  for (auto info : state_.current_program->uniform_block_size_info()) {
    int32_t index = static_cast<int32_t>(info.binding);
    if (index > max_index)
      max_index = index;
  }
  if (max_index < 0)
    return true;
  std::vector<GLsizeiptr> uniform_block_sizes(max_index + 1);
  for (int32_t ii = 0; ii <= max_index; ++ii)
    uniform_block_sizes[ii] = 0;
  for (auto info : state_.current_program->uniform_block_size_info()) {
    uint32_t index = info.binding;
    uniform_block_sizes[index] = static_cast<GLsizeiptr>(info.data_size);
  }
  return buffer_manager()->RequestBuffersAccess(
      state_.GetErrorState(), state_.indexed_uniform_buffer_bindings.get(),
      uniform_block_sizes, 1, func_name, "uniform buffers");
}
