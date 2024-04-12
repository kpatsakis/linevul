void GLES2DecoderImpl::DoDrawBuffersEXT(GLsizei count,
                                        const volatile GLenum* bufs) {
  DCHECK_LE(group_->max_draw_buffers(), 16u);
  if (count > static_cast<GLsizei>(group_->max_draw_buffers())) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_VALUE,
        "glDrawBuffersEXT", "greater than GL_MAX_DRAW_BUFFERS_EXT");
    return;
  }

  Framebuffer* framebuffer = GetFramebufferInfoForTarget(GL_FRAMEBUFFER);
  if (framebuffer) {
    GLenum safe_bufs[16];
    for (GLsizei i = 0; i < count; ++i) {
      GLenum buf = bufs[i];
      if (buf != static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + i) &&
          buf != GL_NONE) {
        LOCAL_SET_GL_ERROR(
            GL_INVALID_OPERATION,
            "glDrawBuffersEXT",
            "bufs[i] not GL_NONE or GL_COLOR_ATTACHMENTi_EXT");
        return;
      }
      safe_bufs[i] = buf;
    }
    api()->glDrawBuffersARBFn(count, safe_bufs);
    framebuffer->SetDrawBuffers(count, safe_bufs);
  } else {  // backbuffer
    if (count != 1) {
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, "glDrawBuffersEXT",
                         "invalid number of buffers");
      return;
    }
    GLenum buf = bufs[0];
    if (buf != GL_BACK && buf != GL_NONE) {
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, "glDrawBuffersEXT",
                         "buffer is not GL_NONE or GL_BACK");
      return;
    }
    back_buffer_draw_buffer_ = buf;
    if (buf == GL_BACK && GetBackbufferServiceId() != 0)  // emulated backbuffer
      buf = GL_COLOR_ATTACHMENT0;
    api()->glDrawBuffersARBFn(count, &buf);
  }
}
