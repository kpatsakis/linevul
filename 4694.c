void GLES2DecoderImpl::DoTexImageIOSurface2DCHROMIUM(
    GLenum target, GLsizei width, GLsizei height,
    GLuint io_surface_id, GLuint plane) {
#if defined(OS_MACOSX)
  if (gfx::GetGLImplementation() != gfx::kGLImplementationDesktopGL) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glTexImageIOSurface2DCHROMIUM", "only supported on desktop GL.");
    return;
  }

  if (target != GL_TEXTURE_RECTANGLE_ARB) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glTexImageIOSurface2DCHROMIUM",
        "requires TEXTURE_RECTANGLE_ARB target");
    return;
  }

  TextureRef* texture_ref =
      texture_manager()->GetTextureInfoForTargetUnlessDefault(&state_, target);
  if (!texture_ref) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glTexImageIOSurface2DCHROMIUM", "no rectangle texture bound");
    return;
  }

  IOSurfaceRef surface = IOSurfaceLookup(io_surface_id);
  if (!surface) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glTexImageIOSurface2DCHROMIUM", "no IOSurface with the given ID");
    return;
  }

  ReleaseIOSurfaceForTexture(texture_ref->service_id());

  texture_to_io_surface_map_.insert(
      std::make_pair(texture_ref->service_id(), surface));

  CGLContextObj context =
      static_cast<CGLContextObj>(context_->GetHandle());

  CGLError err = CGLTexImageIOSurface2D(
      context,
      target,
      GL_RGBA,
      width,
      height,
      GL_BGRA,
      GL_UNSIGNED_INT_8_8_8_8_REV,
      surface,
      plane);

  if (err != kCGLNoError) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glTexImageIOSurface2DCHROMIUM", "error in CGLTexImageIOSurface2D");
    return;
  }

  texture_manager()->SetLevelInfo(
      texture_ref, target, 0, GL_RGBA, width, height, 1, 0,
      GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, true);

#else
  LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION,
             "glTexImageIOSurface2DCHROMIUM", "not supported.");
#endif
}
