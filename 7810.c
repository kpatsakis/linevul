static void RebindCurrentFramebuffer(
    GLenum target,
    FramebufferManager::FramebufferInfo* info,
    GLuint back_buffer_service_id) {
  GLuint framebuffer_id = info ? info->service_id() : 0;

  if (framebuffer_id == 0) {
    framebuffer_id = back_buffer_service_id;
  }

  glBindFramebufferEXT(target, framebuffer_id);
}
