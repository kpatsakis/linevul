bool GLES2DecoderImpl::ClearLevel(
    Texture* texture,
    unsigned target,
    int level,
    unsigned internal_format,
    unsigned format,
    unsigned type,
    int width,
    int height,
    bool is_texture_immutable) {
  uint32 channels = GLES2Util::GetChannelsForFormat(format);
  if (feature_info_->feature_flags().angle_depth_texture &&
      (channels & GLES2Util::kDepth) != 0) {
    GLuint fb = 0;
    glGenFramebuffersEXT(1, &fb);
    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, fb);

    bool have_stencil = (channels & GLES2Util::kStencil) != 0;
    GLenum attachment = have_stencil ? GL_DEPTH_STENCIL_ATTACHMENT :
                                       GL_DEPTH_ATTACHMENT;

    glFramebufferTexture2DEXT(GL_DRAW_FRAMEBUFFER_EXT, attachment, target,
                              texture->service_id(), level);
    if (glCheckFramebufferStatusEXT(GL_DRAW_FRAMEBUFFER_EXT) !=
        GL_FRAMEBUFFER_COMPLETE) {
      return false;
    }
    glClearStencil(0);
    state_.SetDeviceStencilMaskSeparate(GL_FRONT, kDefaultStencilMask);
    state_.SetDeviceStencilMaskSeparate(GL_BACK, kDefaultStencilMask);
    glClearDepth(1.0f);
    state_.SetDeviceDepthMask(GL_TRUE);
    state_.SetDeviceCapabilityState(GL_SCISSOR_TEST, false);
    glClear(GL_DEPTH_BUFFER_BIT | (have_stencil ? GL_STENCIL_BUFFER_BIT : 0));

    RestoreClearState();

    glDeleteFramebuffersEXT(1, &fb);
    Framebuffer* framebuffer =
        GetFramebufferInfoForTarget(GL_DRAW_FRAMEBUFFER_EXT);
    GLuint fb_service_id =
        framebuffer ? framebuffer->service_id() : GetBackbufferServiceId();
    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, fb_service_id);
    return true;
  }

  static const uint32 kMaxZeroSize = 1024 * 1024 * 4;

  uint32 size;
  uint32 padded_row_size;
  if (!GLES2Util::ComputeImageDataSizes(
          width, height, 1, format, type, state_.unpack_alignment, &size,
          NULL, &padded_row_size)) {
    return false;
  }

  TRACE_EVENT1("gpu", "GLES2DecoderImpl::ClearLevel", "size", size);

  int tile_height;

  if (size > kMaxZeroSize) {
    if (kMaxZeroSize < padded_row_size) {
        return false;
    }
    DCHECK_GT(padded_row_size, 0U);
    tile_height = kMaxZeroSize / padded_row_size;
    if (!GLES2Util::ComputeImageDataSizes(
            width, tile_height, 1, format, type, state_.unpack_alignment, &size,
            NULL, NULL)) {
      return false;
    }
  } else {
    tile_height = height;
  }

  scoped_ptr<char[]> zero(new char[size]);
  memset(zero.get(), 0, size);
  glBindTexture(texture->target(), texture->service_id());

  bool has_images = texture->HasImages();
  GLint y = 0;
  while (y < height) {
    GLint h = y + tile_height > height ? height - y : tile_height;
    if (is_texture_immutable || h != height || has_images) {
      glTexSubImage2D(target, level, 0, y, width, h, format, type, zero.get());
    } else {
      glTexImage2D(
          target, level, internal_format, width, h, 0, format, type,
          zero.get());
    }
    y += tile_height;
  }
  TextureRef* bound_texture =
      texture_manager()->GetTextureInfoForTarget(&state_, texture->target());
  glBindTexture(texture->target(),
                bound_texture ? bound_texture->service_id() : 0);
  return true;
}
