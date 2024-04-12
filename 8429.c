void GLES2Implementation::PathCommandsCHROMIUM(GLuint path,
                                               GLsizei num_commands,
                                               const GLubyte* commands,
                                               GLsizei num_coords,
                                               GLenum coord_type,
                                               const void* coords) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glPathCommandsCHROMIUM(" << path
                     << ", " << num_commands << ", " << commands << ", "
                     << num_coords << ", " << coords << ")");
  static const char kFunctionName[] = "glPathCommandsCHROMIUM";
  if (path == 0) {
    SetGLError(GL_INVALID_VALUE, kFunctionName, "invalid path object");
    return;
  }
  if (num_commands < 0) {
    SetGLError(GL_INVALID_VALUE, kFunctionName, "numCommands < 0");
    return;
  }
  if (num_commands != 0 && !commands) {
    SetGLError(GL_INVALID_VALUE, kFunctionName, "missing commands");
    return;
  }
  if (num_coords < 0) {
    SetGLError(GL_INVALID_VALUE, kFunctionName, "numCoords < 0");
    return;
  }
  if (num_coords != 0 && !coords) {
    SetGLError(GL_INVALID_VALUE, kFunctionName, "missing coords");
    return;
  }
  uint32_t coord_type_size =
      GLES2Util::GetGLTypeSizeForPathCoordType(coord_type);
  if (coord_type_size == 0) {
    SetGLError(GL_INVALID_ENUM, kFunctionName, "invalid coordType");
    return;
  }
  if (num_commands == 0) {
    helper_->PathCommandsCHROMIUM(path, num_commands, 0, 0, num_coords,
                                  coord_type, 0, 0);
    CheckGLError();
    return;
  }

  uint32_t coords_size;
  if (!base::CheckMul(num_coords, coord_type_size)
           .AssignIfValid(&coords_size)) {
    SetGLError(GL_INVALID_OPERATION, kFunctionName, "overflow");
    return;
  }

  uint32_t required_buffer_size;
  if (!base::CheckAdd(coords_size, num_commands)
           .AssignIfValid(&required_buffer_size)) {
    SetGLError(GL_INVALID_OPERATION, kFunctionName, "overflow");
    return;
  }

  ScopedTransferBufferPtr buffer(required_buffer_size, helper_,
                                 transfer_buffer_);
  if (!buffer.valid() || buffer.size() < required_buffer_size) {
    SetGLError(GL_OUT_OF_MEMORY, kFunctionName, "too large");
    return;
  }

  uint32_t coords_shm_id = 0;
  uint32_t coords_shm_offset = 0;
  if (coords_size > 0) {
    unsigned char* coords_addr = static_cast<unsigned char*>(buffer.address());
    memcpy(coords_addr, coords, coords_size);
    coords_shm_id = buffer.shm_id();
    coords_shm_offset = buffer.offset();
  }

  DCHECK_GT(num_commands, 0);
  unsigned char* commands_addr =
      static_cast<unsigned char*>(buffer.address()) + coords_size;
  memcpy(commands_addr, commands, num_commands);

  helper_->PathCommandsCHROMIUM(path, num_commands, buffer.shm_id(),
                                buffer.offset() + coords_size, num_coords,
                                coord_type, coords_shm_id, coords_shm_offset);
  CheckGLError();
}
