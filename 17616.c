  explicit ScopedSetBoundsLocally(ClientControlledShellSurface* shell_surface)
      : state_(shell_surface->client_controlled_state_) {
    state_->set_bounds_locally(true);
  }
