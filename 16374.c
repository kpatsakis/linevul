error::Error GLES2DecoderImpl::HandlePathCommandsCHROMIUM(
    uint32_t immediate_data_size,
    const volatile void* cmd_data) {
  static const char kFunctionName[] = "glPathCommandsCHROMIUM";
  const volatile gles2::cmds::PathCommandsCHROMIUM& c =
      *static_cast<const volatile gles2::cmds::PathCommandsCHROMIUM*>(cmd_data);
  if (!features().chromium_path_rendering)
    return error::kUnknownCommand;

  GLuint service_id = 0;
  if (!path_manager()->GetPath(static_cast<GLuint>(c.path), &service_id)) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, kFunctionName,
                       "invalid path name");
    return error::kNoError;
  }

  GLsizei num_commands = static_cast<GLsizei>(c.numCommands);
  if (num_commands < 0) {
    LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, kFunctionName, "numCommands < 0");
    return error::kNoError;
  }

  GLsizei num_coords = static_cast<uint32_t>(c.numCoords);
  if (num_coords < 0) {
    LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, kFunctionName, "numCoords < 0");
    return error::kNoError;
  }

  GLenum coord_type = static_cast<uint32_t>(c.coordType);
  if (!validators_->path_coord_type.IsValid(static_cast<GLint>(coord_type))) {
    LOCAL_SET_GL_ERROR(GL_INVALID_ENUM, kFunctionName, "invalid coordType");
    return error::kNoError;
  }

  std::unique_ptr<GLubyte[]> commands;
  base::CheckedNumeric<GLsizei> num_coords_expected = 0;

  if (num_commands > 0) {
    uint32_t commands_shm_id = static_cast<uint32_t>(c.commands_shm_id);
    uint32_t commands_shm_offset = static_cast<uint32_t>(c.commands_shm_offset);
    if (commands_shm_id != 0 || commands_shm_offset != 0) {
      const GLubyte* shared_commands = GetSharedMemoryAs<const GLubyte*>(
          commands_shm_id, commands_shm_offset, num_commands);
      if (shared_commands) {
        commands.reset(new GLubyte[num_commands]);
        memcpy(commands.get(), shared_commands, num_commands);
      }
    }
    if (!commands)
      return error::kOutOfBounds;

    for (GLsizei i = 0; i < num_commands; ++i) {
      switch (commands[i]) {
        case GL_CLOSE_PATH_CHROMIUM:
          break;
        case GL_MOVE_TO_CHROMIUM:
        case GL_LINE_TO_CHROMIUM:
          num_coords_expected += 2;
          break;
        case GL_QUADRATIC_CURVE_TO_CHROMIUM:
          num_coords_expected += 4;
          break;
        case GL_CUBIC_CURVE_TO_CHROMIUM:
          num_coords_expected += 6;
          break;
        case GL_CONIC_CURVE_TO_CHROMIUM:
          num_coords_expected += 5;
          break;
        default:
          LOCAL_SET_GL_ERROR(GL_INVALID_ENUM, kFunctionName, "invalid command");
          return error::kNoError;
      }
    }
  }

  if (!num_coords_expected.IsValid() ||
      num_coords != num_coords_expected.ValueOrDefault(0)) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, kFunctionName,
                       "numCoords does not match commands");
    return error::kNoError;
  }

  const void* coords = nullptr;

  if (num_coords > 0) {
    uint32_t coords_size = 0;
    uint32_t coord_type_size =
        GLES2Util::GetGLTypeSizeForPathCoordType(coord_type);
    if (!base::CheckMul(num_coords, coord_type_size)
             .AssignIfValid(&coords_size))
      return error::kOutOfBounds;

    uint32_t coords_shm_id = static_cast<uint32_t>(c.coords_shm_id);
    uint32_t coords_shm_offset = static_cast<uint32_t>(c.coords_shm_offset);
    if (coords_shm_id != 0 || coords_shm_offset != 0)
      coords = GetSharedMemoryAs<const void*>(coords_shm_id, coords_shm_offset,
                                              coords_size);

    if (!coords)
      return error::kOutOfBounds;
  }

  api()->glPathCommandsNVFn(service_id, num_commands, commands.get(),
                            num_coords, coord_type, coords);

  return error::kNoError;
}
