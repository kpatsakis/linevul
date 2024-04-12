error::Error GLES2DecoderPassthroughImpl::PatchGetNumericResults(GLenum pname,
                                                                 GLsizei length,
                                                                 T* params) {
  if (length < 1) {
    return error::kNoError;
  }

  switch (pname) {
    case GL_NUM_EXTENSIONS:
      params[0] = 0;
      break;

    case GL_TEXTURE_BINDING_2D:
    case GL_TEXTURE_BINDING_CUBE_MAP:
    case GL_TEXTURE_BINDING_2D_ARRAY:
    case GL_TEXTURE_BINDING_3D:
      if (*params != 0 &&
          !GetClientID(&resources_->texture_id_map, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_ARRAY_BUFFER_BINDING:
    case GL_ELEMENT_ARRAY_BUFFER_BINDING:
    case GL_PIXEL_PACK_BUFFER_BINDING:
    case GL_PIXEL_UNPACK_BUFFER_BINDING:
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:
    case GL_COPY_READ_BUFFER_BINDING:
    case GL_COPY_WRITE_BUFFER_BINDING:
    case GL_UNIFORM_BUFFER_BINDING:
      if (*params != 0 &&
          !GetClientID(&resources_->buffer_id_map, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_RENDERBUFFER_BINDING:
      if (*params != 0 &&
          !GetClientID(&resources_->renderbuffer_id_map, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_SAMPLER_BINDING:
      if (*params != 0 &&
          !GetClientID(&resources_->sampler_id_map, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_ACTIVE_PROGRAM:
      if (*params != 0 &&
          !GetClientID(&resources_->program_id_map, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_FRAMEBUFFER_BINDING:
    case GL_READ_FRAMEBUFFER_BINDING:
      if (*params != 0 && !GetClientID(&framebuffer_id_map_, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_TRANSFORM_FEEDBACK_BINDING:
      if (*params != 0 &&
          !GetClientID(&transform_feedback_id_map_, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_VERTEX_ARRAY_BINDING:
      if (*params != 0 &&
          !GetClientID(&vertex_array_id_map_, *params, params)) {
        return error::kInvalidArguments;
      }
      break;

    case GL_VIEWPORT:
      if (length < 4) {
        return error::kInvalidArguments;
      }
      std::copy(std::begin(viewport_), std::end(viewport_), params);
      break;

    case GL_SCISSOR_BOX:
      if (length < 4) {
        return error::kInvalidArguments;
      }
      std::copy(std::begin(scissor_), std::end(scissor_), params);
      break;

    default:
      break;
  }

  return error::kNoError;
}
