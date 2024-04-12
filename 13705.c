  ~ScopedBrowserShower() {
    if (params_->window_action == NavigateParams::SHOW_WINDOW_INACTIVE) {
      params_->browser->window()->ShowInactive();
    } else if (params_->window_action == NavigateParams::SHOW_WINDOW) {
      BrowserWindow* window = params_->browser->window();
      window->Show();
      if (params_->user_gesture &&
          params_->disposition == WindowOpenDisposition::NEW_POPUP &&
          *contents_) {
        (*contents_)->Focus();
        window->Activate();
      }
    }
  }
