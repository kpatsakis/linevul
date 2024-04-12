error::Error GLES2DecoderPassthroughImpl::DoResizeCHROMIUM(GLuint width,
                                                           GLuint height,
                                                           GLfloat scale_factor,
                                                           GLenum color_space,
                                                           GLboolean alpha) {
  static_assert(sizeof(GLuint) >= sizeof(int), "Unexpected GLuint size.");
  static const GLuint kMaxDimension =
      static_cast<GLuint>(std::numeric_limits<int>::max());
  gfx::Size safe_size(std::min(std::max(1U, width), kMaxDimension),
                      std::min(std::max(1U, height), kMaxDimension));
  if (offscreen_) {
    if (!ResizeOffscreenFramebuffer(safe_size)) {
      LOG(ERROR) << "GLES2DecoderPassthroughImpl: Context lost because "
                 << "ResizeOffscreenFramebuffer failed.";
      return error::kLostContext;
    }
  } else {
    gl::GLSurface::ColorSpace surface_color_space =
        gl::GLSurface::ColorSpace::UNSPECIFIED;
    switch (color_space) {
      case GL_COLOR_SPACE_UNSPECIFIED_CHROMIUM:
        surface_color_space = gl::GLSurface::ColorSpace::UNSPECIFIED;
        break;
      case GL_COLOR_SPACE_SCRGB_LINEAR_CHROMIUM:
        surface_color_space = gl::GLSurface::ColorSpace::SCRGB_LINEAR;
        break;
      case GL_COLOR_SPACE_HDR10_CHROMIUM:
        surface_color_space = gl::GLSurface::ColorSpace::HDR10;
        break;
      case GL_COLOR_SPACE_SRGB_CHROMIUM:
        surface_color_space = gl::GLSurface::ColorSpace::SRGB;
        break;
      case GL_COLOR_SPACE_DISPLAY_P3_CHROMIUM:
        surface_color_space = gl::GLSurface::ColorSpace::DISPLAY_P3;
        break;
      default:
        LOG(ERROR) << "GLES2DecoderPassthroughImpl: Context lost because "
                      "specified color space was invalid.";
        return error::kLostContext;
    }
    if (!surface_->Resize(safe_size, scale_factor, surface_color_space,
                          !!alpha)) {
      LOG(ERROR)
          << "GLES2DecoderPassthroughImpl: Context lost because resize failed.";
      return error::kLostContext;
    }
    DCHECK(context_->IsCurrent(surface_.get()));
    if (!context_->IsCurrent(surface_.get())) {
      LOG(ERROR) << "GLES2DecoderPassthroughImpl: Context lost because context "
                    "no longer current after resize callback.";
      return error::kLostContext;
    }
  }
  return error::kNoError;
}
