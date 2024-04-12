void ClientControlledShellSurface::OnWindowAddedToRootWindow(
    aura::Window* window) {
  if (client_controlled_state_->set_bounds_locally())
    return;

  ScopedLockedToRoot scoped_locked_to_root(widget_);
  UpdateWidgetBounds();
}
