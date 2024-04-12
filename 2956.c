void FramebufferManager::MarkAttachmentsAsCleared(
    Framebuffer* framebuffer,
    RenderbufferManager* renderbuffer_manager,
    TextureManager* texture_manager) {
  DCHECK(framebuffer);
  framebuffer->MarkAttachmentsAsCleared(renderbuffer_manager,
                                        texture_manager,
                                        true);
  MarkAsComplete(framebuffer);
}
