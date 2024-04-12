std::unique_ptr<AbstractTexture> GLES2DecoderImpl::CreateAbstractTexture(
    GLenum target,
    GLenum internal_format,
    GLsizei width,
    GLsizei height,
    GLsizei depth,
    GLint border,
    GLenum format,
    GLenum type) {
  GLuint service_id = 0;
  api()->glGenTexturesFn(1, &service_id);
  scoped_refptr<gpu::gles2::TextureRef> texture_ref =
      TextureRef::Create(texture_manager(), 0, service_id);
  texture_manager()->SetTarget(texture_ref.get(), target);
  const GLint level = 0;
  gfx::Rect cleared_rect = gfx::Rect();
  texture_manager()->SetLevelInfo(texture_ref.get(), target, level,
                                  internal_format, width, height, depth, border,
                                  format, type, cleared_rect);

  std::unique_ptr<ValidatingAbstractTextureImpl> abstract_texture =
      std::make_unique<ValidatingAbstractTextureImpl>(
          std::move(texture_ref), this,
          base::BindOnce(&GLES2DecoderImpl::OnAbstractTextureDestroyed,
                         base::Unretained(this)));
  abstract_textures_.insert(abstract_texture.get());

  return abstract_texture;
}
