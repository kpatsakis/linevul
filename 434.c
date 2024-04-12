GLES2DecoderPassthroughImpl::TexturePendingBinding::TexturePendingBinding(
    GLenum target,
    GLuint unit,
    base::WeakPtr<TexturePassthrough> texture)
    : target(target), unit(unit), texture(std::move(texture)) {}
