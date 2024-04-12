void GLES2DecoderImpl::DoRenderbufferStorage(
  GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
  if (!bound_renderbuffer_) {
    SetGLError(GL_INVALID_OPERATION,
               "glGetRenderbufferStorage: no renderbuffer bound");
    return;
  }

  GLenum impl_format = internalformat;
  if (gfx::GetGLImplementation() != gfx::kGLImplementationEGLGLES2) {
    switch (impl_format) {
      case GL_DEPTH_COMPONENT16:
        impl_format = GL_DEPTH_COMPONENT;
        break;
      case GL_RGBA4:
      case GL_RGB5_A1:
        impl_format = GL_RGBA;
        break;
      case GL_RGB565:
        impl_format = GL_RGB;
        break;
    }
  }

  CopyRealGLErrorsToWrapper();
  glRenderbufferStorageEXT(target, impl_format, width, height);
  GLenum error = PeekGLError();
  if (error == GL_NO_ERROR) {
    bound_renderbuffer_->SetInfo(0, internalformat, width, height);
  }
}
