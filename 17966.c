  ~ScopedBrowserDisplayer() {
    if (params_->window_action == browser::NavigateParams::SHOW_WINDOW_INACTIVE)
      params_->browser->window()->ShowInactive();
    else if (params_->window_action == browser::NavigateParams::SHOW_WINDOW)
      params_->browser->window()->Show();
  }
