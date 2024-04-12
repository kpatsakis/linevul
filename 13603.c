ClientControlledShellSurface::ClientControlledShellSurface(Surface* surface,
                                                           bool can_minimize,
                                                           int container)
    : ShellSurfaceBase(surface, gfx::Point(), true, can_minimize, container) {
  display::Screen::GetScreen()->AddObserver(this);
}
