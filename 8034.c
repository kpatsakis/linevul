void GLES2DecoderImpl::DoBlitFramebufferCHROMIUM(
    GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
    GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
    GLbitfield mask, GLenum filter) {
  const char* func_name = "glBlitFramebufferCHROMIUM";
  DCHECK(!ShouldDeferReads() && !ShouldDeferDraws());

  if (!CheckBoundFramebufferValid(func_name)) {
    return;
  }

  if (GetBoundFramebufferSamples(GL_DRAW_FRAMEBUFFER) > 0) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
                       "destination framebuffer is multisampled");
    return;
  }

  GLsizei read_buffer_samples = GetBoundFramebufferSamples(GL_READ_FRAMEBUFFER);
  if (read_buffer_samples > 0 &&
      (srcX0 != dstX0 || srcY0 != dstY0 || srcX1 != dstX1 || srcY1 != dstY1)) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
        "src framebuffer is multisampled, but src/dst regions are different");
    return;
  }

  GLbitfield mask_blit = mask;

  bool read_framebuffer_miss_image = false;

  enum FeedbackLoopState {
    FeedbackLoopTrue,
    FeedbackLoopFalse,
    FeedbackLoopUnknown
  };

  FeedbackLoopState is_feedback_loop = FeedbackLoopUnknown;
  Framebuffer* read_framebuffer =
      framebuffer_state_.bound_read_framebuffer.get();
  Framebuffer* draw_framebuffer =
      framebuffer_state_.bound_draw_framebuffer.get();
  if (!read_framebuffer && !draw_framebuffer) {
    is_feedback_loop = FeedbackLoopTrue;
  } else if (!read_framebuffer || !draw_framebuffer) {
    is_feedback_loop = FeedbackLoopFalse;
    if (read_framebuffer) {
      if (((mask & GL_COLOR_BUFFER_BIT) != 0 &&
          !GetBoundReadFramebufferInternalFormat()) ||
          ((mask & GL_DEPTH_BUFFER_BIT) != 0 &&
          !read_framebuffer->GetAttachment(GL_DEPTH_ATTACHMENT) &&
          BoundFramebufferHasDepthAttachment()) ||
          ((mask & GL_STENCIL_BUFFER_BIT) != 0 &&
          !read_framebuffer->GetAttachment(GL_STENCIL_ATTACHMENT) &&
          BoundFramebufferHasStencilAttachment())) {
        read_framebuffer_miss_image = true;
      }
    }
  } else {
    DCHECK(read_framebuffer && draw_framebuffer);
    if ((mask & GL_DEPTH_BUFFER_BIT) != 0) {
      const Framebuffer::Attachment* depth_buffer_read =
          read_framebuffer->GetAttachment(GL_DEPTH_ATTACHMENT);
      const Framebuffer::Attachment* depth_buffer_draw =
          draw_framebuffer->GetAttachment(GL_DEPTH_ATTACHMENT);
      if (!depth_buffer_draw || !depth_buffer_read) {
        mask_blit &= ~GL_DEPTH_BUFFER_BIT;
        if (depth_buffer_draw) {
          read_framebuffer_miss_image = true;
        }
      } else if (depth_buffer_draw->IsSameAttachment(depth_buffer_read)) {
        is_feedback_loop = FeedbackLoopTrue;
      }
    }
    if ((mask & GL_STENCIL_BUFFER_BIT) != 0) {
      const Framebuffer::Attachment* stencil_buffer_read =
          read_framebuffer->GetAttachment(GL_STENCIL_ATTACHMENT);
      const Framebuffer::Attachment* stencil_buffer_draw =
          draw_framebuffer->GetAttachment(GL_STENCIL_ATTACHMENT);
      if (!stencil_buffer_draw || !stencil_buffer_read) {
        mask_blit &= ~GL_STENCIL_BUFFER_BIT;
        if (stencil_buffer_draw) {
          read_framebuffer_miss_image = true;
        }
      } else if (stencil_buffer_draw->IsSameAttachment(stencil_buffer_read)) {
        is_feedback_loop = FeedbackLoopTrue;
      }
    }
  }

  GLenum src_internal_format = GetBoundReadFramebufferInternalFormat();
  GLenum src_type = GetBoundReadFramebufferTextureType();

  bool read_buffer_has_srgb = GLES2Util::GetColorEncodingFromInternalFormat(
                                  src_internal_format) == GL_SRGB;
  bool draw_buffers_has_srgb = false;
  if ((mask & GL_COLOR_BUFFER_BIT) != 0) {
    bool is_src_signed_int =
        GLES2Util::IsSignedIntegerFormat(src_internal_format);
    bool is_src_unsigned_int =
        GLES2Util::IsUnsignedIntegerFormat(src_internal_format);
    DCHECK(!is_src_signed_int || !is_src_unsigned_int);

    if ((is_src_signed_int || is_src_unsigned_int) && filter == GL_LINEAR) {
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
                         "invalid filter for integer format");
      return;
    }

    GLenum src_sized_format =
        GLES2Util::ConvertToSizedFormat(src_internal_format, src_type);
    DCHECK(read_framebuffer || (is_feedback_loop != FeedbackLoopUnknown));
    const Framebuffer::Attachment* read_buffer =
        is_feedback_loop == FeedbackLoopUnknown ?
        read_framebuffer->GetReadBufferAttachment() : nullptr;
    bool draw_buffer_has_image = false;
    for (uint32_t ii = 0; ii < group_->max_draw_buffers(); ++ii) {
      GLenum dst_format = GetBoundColorDrawBufferInternalFormat(
          static_cast<GLint>(ii));
      GLenum dst_type = GetBoundColorDrawBufferType(static_cast<GLint>(ii));
      if (dst_format == 0)
        continue;
      draw_buffer_has_image = true;
      if (!src_internal_format) {
        read_framebuffer_miss_image = true;
      }
      if (GLES2Util::GetColorEncodingFromInternalFormat(dst_format) == GL_SRGB)
        draw_buffers_has_srgb = true;
      if (read_buffer_samples > 0 &&
          (src_sized_format !=
           GLES2Util::ConvertToSizedFormat(dst_format, dst_type))) {
        LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
                           "src and dst formats differ for color");
        return;
      }
      bool is_dst_signed_int = GLES2Util::IsSignedIntegerFormat(dst_format);
      bool is_dst_unsigned_int = GLES2Util::IsUnsignedIntegerFormat(dst_format);
      DCHECK(!is_dst_signed_int || !is_dst_unsigned_int);
      if (is_src_signed_int != is_dst_signed_int ||
          is_src_unsigned_int != is_dst_unsigned_int) {
        LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
                           "incompatible src/dst color formats");
        return;
      }
      if (is_feedback_loop == FeedbackLoopUnknown) {
        GLenum attachment = static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + ii);
        DCHECK(draw_framebuffer);
        const Framebuffer::Attachment* draw_buffer =
            draw_framebuffer->GetAttachment(attachment);
        if (!draw_buffer || !read_buffer) {
          continue;
        }
        if (draw_buffer->IsSameAttachment(read_buffer)) {
          is_feedback_loop = FeedbackLoopTrue;
          break;
        }
      }
    }
    if (draw_framebuffer && !draw_buffer_has_image)
      mask_blit &= ~GL_COLOR_BUFFER_BIT;
  }
  if (is_feedback_loop == FeedbackLoopTrue) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
        "source buffer and destination buffers are identical");
    return;
  }
  if (read_framebuffer_miss_image == true) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
       "The designated attachment point(s) in read framebuffer miss image");
    return;
  }

  if ((mask & (GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)) != 0) {
    if (filter != GL_NEAREST) {
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
                         "invalid filter for depth/stencil");
      return;
    }
  }

  mask = mask_blit;
  if (!mask)
    return;

  if (((mask & GL_DEPTH_BUFFER_BIT) != 0 &&
      (GetBoundFramebufferDepthFormat(GL_READ_FRAMEBUFFER) !=
      GetBoundFramebufferDepthFormat(GL_DRAW_FRAMEBUFFER))) ||
      ((mask & GL_STENCIL_BUFFER_BIT) != 0 &&
      ((GetBoundFramebufferStencilFormat(GL_READ_FRAMEBUFFER) !=
      GetBoundFramebufferStencilFormat(GL_DRAW_FRAMEBUFFER))))) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
                       "src and dst formats differ for depth/stencil");
    return;
  }

  base::CheckedNumeric<GLint> src_width_temp = srcX1;
  src_width_temp -= srcX0;
  base::CheckedNumeric<GLint> src_height_temp = srcY1;
  src_height_temp -= srcY0;
  base::CheckedNumeric<GLint> dst_width_temp = dstX1;
  dst_width_temp -= dstX0;
  base::CheckedNumeric<GLint> dst_height_temp = dstY1;
  dst_height_temp -= dstY0;
  if (!src_width_temp.Abs().IsValid() || !src_height_temp.Abs().IsValid() ||
      !dst_width_temp.Abs().IsValid() || !dst_height_temp.Abs().IsValid()) {
    LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, func_name,
                       "the width or height of src or dst region overflowed");
    return;
  }

  if (workarounds().adjust_src_dst_region_for_blitframebuffer) {
    gfx::Size read_size = GetBoundReadFramebufferSize();
    gfx::Rect src_bounds(0, 0, read_size.width(), read_size.height());
    GLint src_x = srcX1 > srcX0 ? srcX0 : srcX1;
    GLint src_y = srcY1 > srcY0 ? srcY0 : srcY1;
    GLuint src_width = 0, src_height = 0;
    if (!src_width_temp.Abs().AssignIfValid(&src_width))
      src_width = 0;
    if (!src_height_temp.Abs().AssignIfValid(&src_height))
      src_height = 0;

    gfx::Rect src_region(src_x, src_y, src_width, src_height);
    if (!src_bounds.Contains(src_region) &&
        (src_width != 0) && (src_height != 0)) {
      src_bounds.Intersect(src_region);
      GLuint src_real_width = src_bounds.width();
      GLuint src_real_height = src_bounds.height();
      GLuint xoffset = src_bounds.x() - src_x;
      GLuint yoffset = src_bounds.y() - src_y;
      if (((srcX1 > srcX0) && (dstX1 < dstX0)) ||
          ((srcX1 < srcX0) && (dstX1 > dstX0))) {
        xoffset = src_x + src_width - src_bounds.x() - src_bounds.width();
      }
      if (((srcY1 > srcY0) && (dstY1 < dstY0)) ||
          ((srcY1 < srcY0) && (dstY1 > dstY0))) {
        yoffset = src_y + src_height - src_bounds.y() - src_bounds.height();
      }

      GLint dst_x = dstX1 > dstX0 ? dstX0 : dstX1;
      GLint dst_y = dstY1 > dstY0 ? dstY0 : dstY1;
      base::CheckedNumeric<GLint> dst_width_temp = dstX1;
      dst_width_temp -= dstX0;
      base::CheckedNumeric<GLint> dst_height_temp = dstY1;
      dst_height_temp -= dstY0;
      GLuint dst_width = 0, dst_height = 0;
      if (!dst_width_temp.IsValid() || !dst_height_temp.IsValid()) {
        LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, func_name,
                           "the width or height of dst region overflow");
        return;
      }
      if (!dst_width_temp.Abs().AssignIfValid(&dst_width))
        dst_width = 0;
      if (!dst_height_temp.Abs().AssignIfValid(&dst_height))
        dst_height = 0;

      GLfloat dst_mapping_width =
          static_cast<GLfloat>(src_real_width) * dst_width / src_width;
      GLfloat dst_mapping_height =
          static_cast<GLfloat>(src_real_height) * dst_height / src_height;
      GLfloat dst_mapping_xoffset =
          static_cast<GLfloat>(xoffset) * dst_width / src_width;
      GLfloat dst_mapping_yoffset =
          static_cast<GLfloat>(yoffset) * dst_height / src_height;

      GLuint dst_mapping_x0 =
          std::round(dst_x + dst_mapping_xoffset);
      GLuint dst_mapping_y0 =
          std::round(dst_y + dst_mapping_yoffset);

      GLuint dst_mapping_x1 =
          std::round(dst_x + dst_mapping_xoffset + dst_mapping_width);
      GLuint dst_mapping_y1 =
          std::round(dst_y + dst_mapping_yoffset + dst_mapping_height);

      srcX0 = srcX0 < srcX1 ?
          src_bounds.x() : src_bounds.x() + src_bounds.width();
      srcY0 = srcY0 < srcY1 ?
          src_bounds.y() : src_bounds.y() + src_bounds.height();
      srcX1 = srcX0 < srcX1 ?
          src_bounds.x() + src_bounds.width() : src_bounds.x();
      srcY1 = srcY0 < srcY1 ?
          src_bounds.y() + src_bounds.height() : src_bounds.y();

      dstX0 = dstX0 < dstX1 ? dst_mapping_x0 : dst_mapping_x1;
      dstY0 = dstY0 < dstY1 ? dst_mapping_y0 : dst_mapping_y1;
      dstX1 = dstX0 < dstX1 ? dst_mapping_x1 : dst_mapping_x0;
      dstY1 = dstY0 < dstY1 ? dst_mapping_y1 : dst_mapping_y0;
    }
  }

  bool enable_srgb =
      (read_buffer_has_srgb || draw_buffers_has_srgb) &&
      ((mask & GL_COLOR_BUFFER_BIT) != 0);
  bool encode_srgb_only =
      (draw_buffers_has_srgb && !read_buffer_has_srgb) &&
      ((mask & GL_COLOR_BUFFER_BIT) != 0);
  if (!enable_srgb ||
      read_buffer_samples > 0 ||
      !feature_info_->feature_flags().desktop_srgb_support ||
      gl_version_info().IsAtLeastGL(4, 4) ||
      (gl_version_info().IsAtLeastGL(4, 2) && encode_srgb_only)) {
    if (enable_srgb && gl_version_info().IsAtLeastGL(4, 2)) {
      state_.EnableDisableFramebufferSRGB(enable_srgb);
    }

    api()->glBlitFramebufferFn(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1,
                               dstY1, mask, filter);
    return;
  }

  state_.EnableDisableFramebufferSRGB(true);
  if (!InitializeSRGBConverter(func_name)) {
    return;
  }
  GLenum src_format =
      TextureManager::ExtractFormatFromStorageFormat(src_internal_format);
  srgb_converter_->Blit(this, srcX0, srcY0, srcX1, srcY1,
                        dstX0, dstY0, dstX1, dstY1,
                        mask, filter,
                        GetBoundReadFramebufferSize(),
                        GetBoundReadFramebufferServiceId(),
                        src_internal_format, src_format, src_type,
                        GetBoundDrawFramebufferServiceId(),
                        read_buffer_has_srgb, draw_buffers_has_srgb,
                        state_.enable_flags.scissor_test);
}
