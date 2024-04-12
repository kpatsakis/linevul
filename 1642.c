bool DrawingBuffer::FinishPrepareTextureMailboxSoftware(
    viz::TextureMailbox* out_mailbox,
    std::unique_ptr<cc::SingleReleaseCallback>* out_release_callback) {
  DCHECK(state_restorer_);
  std::unique_ptr<viz::SharedBitmap> bitmap = CreateOrRecycleBitmap();
  if (!bitmap)
    return false;

  {
    unsigned char* pixels = bitmap->pixels();
    DCHECK(pixels);
    bool need_premultiply = want_alpha_channel_ && !premultiplied_alpha_;
    WebGLImageConversion::AlphaOp op =
        need_premultiply ? WebGLImageConversion::kAlphaDoPremultiply
                         : WebGLImageConversion::kAlphaDoNothing;
    state_restorer_->SetFramebufferBindingDirty();
    gl_->BindFramebuffer(GL_FRAMEBUFFER, fbo_);
    ReadBackFramebuffer(pixels, Size().Width(), Size().Height(), kReadbackSkia,
                        op);
  }

  *out_mailbox = viz::TextureMailbox(bitmap.get(), size_);
  out_mailbox->set_color_space(color_space_);

  auto func = WTF::Bind(&DrawingBuffer::MailboxReleasedSoftware,
                        RefPtr<DrawingBuffer>(this),
                        WTF::Passed(std::move(bitmap)), size_);
  *out_release_callback =
      cc::SingleReleaseCallback::Create(ConvertToBaseCallback(std::move(func)));

  if (preserve_drawing_buffer_ == kDiscard) {
    SetBufferClearNeeded(true);
  }

  return true;
}
