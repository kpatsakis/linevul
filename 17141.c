bool GLSurfaceOzoneSurfacelessSurfaceImpl::CreatePixmaps() {
  if (!fbo_)
    return true;
  for (size_t i = 0; i < arraysize(textures_); i++) {
    scoped_refptr<ui::NativePixmap> pixmap =
        ui::OzonePlatform::GetInstance()
            ->GetSurfaceFactoryOzone()
            ->CreateNativePixmap(widget_, GetSize(),
                                 gfx::BufferFormat::BGRA_8888,
                                 gfx::BufferUsage::SCANOUT);
    if (!pixmap)
      return false;
    scoped_refptr<GLImageOzoneNativePixmap> image =
        new GLImageOzoneNativePixmap(GetSize(), GL_BGRA_EXT);
    if (!image->Initialize(pixmap.get(), gfx::BufferFormat::BGRA_8888))
      return false;
    if (images_[i])
      images_[i]->Destroy(true);
    images_[i] = image;
    ScopedTextureBinder binder(GL_TEXTURE_2D, textures_[i]);
    if (!images_[i]->BindTexImage(GL_TEXTURE_2D))
      return false;
  }
  return true;
}
