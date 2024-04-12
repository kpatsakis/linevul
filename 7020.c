void GLES2DecoderImpl::DoReleaseTexImage2DCHROMIUM(
    GLenum target, GLint image_id) {
  TRACE_EVENT0("gpu", "GLES2DecoderImpl::DoReleaseTexImage2DCHROMIUM");

  TextureRef* texture_ref =
      texture_manager()->GetTextureInfoForTargetUnlessDefault(&state_, target);
  if (!texture_ref) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glReleaseTexImage2DCHROMIUM", "no texture bound");
    return;
  }

  gl::GLImage* image = image_manager()->LookupImage(image_id);
  if (!image) {
    LOCAL_SET_GL_ERROR(
        GL_INVALID_OPERATION,
        "glReleaseTexImage2DCHROMIUM", "no image found with the given ID");
    return;
  }

  Texture::ImageState image_state;

  if (texture_ref->texture()->GetLevelImage(target, 0, &image_state) != image)
    return;

  if (image_state == Texture::BOUND) {
    ScopedGLErrorSuppressor suppressor(
        "GLES2DecoderImpl::DoReleaseTexImage2DCHROMIUM", GetErrorState());

    image->ReleaseTexImage(target);
    texture_manager()->SetLevelInfo(texture_ref, target, 0, GL_RGBA, 0, 0, 1, 0,
                                    GL_RGBA, GL_UNSIGNED_BYTE, gfx::Rect());
  }

  texture_manager()->SetLevelImage(texture_ref, target, 0, nullptr,
                                   Texture::UNBOUND);
}
