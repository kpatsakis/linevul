void GLES2DecoderPassthroughImpl::EmulatedColorBuffer::Resize(
    const gfx::Size& new_size) {
  if (size == new_size)
    return;
  size = new_size;

  ScopedTexture2DBindingReset scoped_texture_reset(api);

  DCHECK(texture);
  DCHECK(texture->target() == GL_TEXTURE_2D);

  api->glBindTextureFn(texture->target(), texture->service_id());
  api->glTexImage2DFn(texture->target(), 0,
                      format.color_texture_internal_format, size.width(),
                      size.height(), 0, format.color_texture_format,
                      format.color_texture_type, nullptr);
  UpdateBoundTexturePassthroughSize(api, texture.get());
}
