bool GLES2DecoderImpl::ClearLevel(
    unsigned service_id,
    unsigned bind_target,
    unsigned target,
    int level,
    unsigned format,
    unsigned type,
    int width,
    int height,
    bool is_texture_immutable) {
  uint32 channels = GLES2Util::GetChannelsForFormat(format);
  if (IsAngle() && (channels & GLES2Util::kDepth) != 0) {
    GLuint fb = 0;
    glGenFramebuffersEXT(1, &fb);
    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, fb);

    bool have_stencil = (channels & GLES2Util::kStencil) != 0;
    GLenum attachment = have_stencil ? GL_DEPTH_STENCIL_ATTACHMENT :
                                       GL_DEPTH_ATTACHMENT;

    glFramebufferTexture2DEXT(
        GL_DRAW_FRAMEBUFFER_EXT, attachment, target, service_id, level);
    if (glCheckFramebufferStatusEXT(GL_DRAW_FRAMEBUFFER_EXT) !=
        GL_FRAMEBUFFER_COMPLETE) {
      return false;
    }
    glClearStencil(0);
    glStencilMask(-1);
    glClearDepth(1.0f);
    glDepthMask(true);
    glDisable(GL_SCISSOR_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | (have_stencil ? GL_STENCIL_BUFFER_BIT : 0));

    RestoreClearState();

    glDeleteFramebuffersEXT(1, &fb);
    FramebufferManager::FramebufferInfo* framebuffer =
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
          width, height, format, type, unpack_alignment_, &size,
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
            width, tile_height, format, type, unpack_alignment_, &size, NULL,
            NULL)) {
      return false;
    }
  } else {
    tile_height = height;
  }

  scoped_array<char> zero(new char[size]);
  memset(zero.get(), 0, size);
  glBindTexture(bind_target, service_id);

  GLint y = 0;
  while (y < height) {
    GLint h = y + tile_height > height ? height - y : tile_height;
    if (is_texture_immutable || h != height) {
      glTexSubImage2D(target, level, 0, y, width, h, format, type, zero.get());
    } else {
      WrappedTexImage2D(
          target, level, format, width, h, 0, format, type, zero.get());
    }
    y += tile_height;
  }
  TextureManager::TextureInfo* info = GetTextureInfoForTarget(bind_target);
  glBindTexture(bind_target, info ? info->service_id() : 0);
  return true;
}
