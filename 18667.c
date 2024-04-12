ScopedRenderTo::ScopedRenderTo(Framebuffer* framebuffer)
    : framebuffer_(framebuffer) {
  if (framebuffer)
    framebuffer_->OnWillRenderTo();
}
