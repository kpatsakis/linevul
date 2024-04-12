  ~ScopedCommitStateResetter() {
    if (!disabled_) {
      render_frame_host_->set_nav_entry_id(0);
    }
  }
