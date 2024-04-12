error::Error GLES2DecoderImpl::HandleDrawArrays(uint32_t immediate_data_size,
                                                const volatile void* cmd_data) {
  const volatile cmds::DrawArrays& c =
      *static_cast<const volatile cmds::DrawArrays*>(cmd_data);
  GLint first = static_cast<GLint>(c.first);
  GLsizei count = static_cast<GLsizei>(c.count);
  return DoMultiDrawArrays("glDrawArrays", false, static_cast<GLenum>(c.mode),
                           &first, &count, nullptr, 1);
}
