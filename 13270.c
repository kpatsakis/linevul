  void UnlockCompositor() {
    defer_compositor_lock_ = false;
    compositor_lock_ = NULL;
  }
