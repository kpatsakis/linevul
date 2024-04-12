void GLES2DecoderImpl::DoApplyScreenSpaceAntialiasingCHROMIUM() {
  Framebuffer* bound_framebuffer =
      GetFramebufferInfoForTarget(GL_DRAW_FRAMEBUFFER);
  if (!bound_framebuffer) {
    LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION,
                       "glApplyScreenSpaceAntialiasingCHROMIUM",
                       "no bound framebuffer object");
    return;
  }

  if (!feature_info_->feature_flags()
           .use_chromium_screen_space_antialiasing_via_shaders) {
    api()->glApplyFramebufferAttachmentCMAAINTELFn();
  } else {
    if (!apply_framebuffer_attachment_cmaa_intel_.get()) {
      LOCAL_COPY_REAL_GL_ERRORS_TO_WRAPPER(
          "glApplyFramebufferAttachmentCMAAINTEL");
      apply_framebuffer_attachment_cmaa_intel_.reset(
          new ApplyFramebufferAttachmentCMAAINTELResourceManager());
      apply_framebuffer_attachment_cmaa_intel_->Initialize(this);
      if (LOCAL_PEEK_GL_ERROR("glApplyFramebufferAttachmentCMAAINTEL") !=
          GL_NO_ERROR)
        return;
    }
    static const char kFunctionName[] =
        "glApplyScreenSpaceAntialiasingCHROMIUM";
    if (!InitializeCopyTextureCHROMIUM(kFunctionName))
      return;
    for (uint32_t i = 0; i < group_->max_draw_buffers(); ++i) {
      const Framebuffer::Attachment* attachment =
          bound_framebuffer->GetAttachment(GL_COLOR_ATTACHMENT0 + i);
      if (attachment && attachment->IsTextureAttachment()) {
        GLenum internal_format = attachment->internal_format();
        if (!CanUseCopyTextureCHROMIUMInternalFormat(internal_format)) {
          LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, kFunctionName,
                             "Apply CMAA on framebuffer with attachment in "
                             "invalid internalformat.");
          return;
        }
      }
    }

    apply_framebuffer_attachment_cmaa_intel_
        ->ApplyFramebufferAttachmentCMAAINTEL(this, bound_framebuffer,
                                              copy_texture_chromium_.get(),
                                              texture_manager());
  }
}
