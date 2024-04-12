void Framebuffer::AttachRenderbuffer(
    GLenum attachment, Renderbuffer* renderbuffer) {
  const Attachment* a = GetAttachment(attachment);
  if (a)
    a->DetachFromFramebuffer(this);
  if (renderbuffer) {
    attachments_[attachment] = scoped_refptr<Attachment>(
        new RenderbufferAttachment(renderbuffer));
  } else {
    attachments_.erase(attachment);
  }
  framebuffer_complete_state_count_id_ = 0;
}
