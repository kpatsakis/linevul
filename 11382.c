gfx::Rect ShellSurface::GetVisibleBounds() const {
  return geometry_.IsEmpty() ? gfx::Rect(surface_->window()->layer()->size())
                             : geometry_;
}
