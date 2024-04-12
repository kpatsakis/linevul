DXVAVideoDecodeAccelerator::DXVAPictureBuffer::~DXVAPictureBuffer() {
  if (decoding_surface_) {
    eglReleaseTexImage(
        static_cast<EGLDisplay*>(eglGetDisplay(EGL_DEFAULT_DISPLAY)),
        decoding_surface_,
        EGL_BACK_BUFFER);

    eglDestroySurface(
        static_cast<EGLDisplay*>(eglGetDisplay(EGL_DEFAULT_DISPLAY)),
        decoding_surface_);
    decoding_surface_ = NULL;
  }
}
