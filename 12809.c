GLSurfaceEGLSurfaceControl::SurfaceState::SurfaceState(
    const SurfaceControl::Surface& parent)
    : surface(new SurfaceControl::Surface(parent, kChildSurfaceName)) {}
