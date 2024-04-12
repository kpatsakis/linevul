bool GLSurface::InitializeOneOffInternal() {
  switch (GetGLImplementation()) {
    case kGLImplementationEGLGLES2:
      if (!GLSurfaceEGL::InitializeOneOff()) {
        LOG(ERROR) << "GLSurfaceEGL::InitializeOneOff failed.";
        return false;
      }

      return true;
    case kGLImplementationOSMesaGL:
    case kGLImplementationMockGL:
      return true;
    default:
      return false;
  }
}
