error::Error GLES2DecoderImpl::HandleDrawArraysInstancedANGLE(
    uint32 immediate_data_size,
    const void* cmd_data) {
  const gles2::cmds::DrawArraysInstancedANGLE& c =
      *static_cast<const gles2::cmds::DrawArraysInstancedANGLE*>(cmd_data);
  if (!features().angle_instanced_arrays) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glDrawArraysInstancedANGLE", "function not available");
    return error::kNoError;
  }
  return DoDrawArrays("glDrawArraysIntancedANGLE",
                      true,
                      static_cast<GLenum>(c.mode),
                      static_cast<GLint>(c.first),
                      static_cast<GLsizei>(c.count),
                      static_cast<GLsizei>(c.primcount));
}
