error::Error GLES2DecoderImpl::HandleDrawElementsInstancedANGLE(
    uint32_t immediate_data_size,
    const volatile void* cmd_data) {
  const volatile gles2::cmds::DrawElementsInstancedANGLE& c =
      *static_cast<const volatile gles2::cmds::DrawElementsInstancedANGLE*>(
          cmd_data);
  if (!features().angle_instanced_arrays)
    return error::kUnknownCommand;

  GLsizei count = static_cast<GLsizei>(c.count);
  int32_t offset = static_cast<int32_t>(c.index_offset);
  GLsizei primcount = static_cast<GLsizei>(c.primcount);
  return DoMultiDrawElements(
      "glDrawElementsInstancedANGLE", true, static_cast<GLenum>(c.mode), &count,
      static_cast<GLenum>(c.type), &offset, &primcount, 1);
}
