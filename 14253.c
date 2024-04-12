  void Run() {
    g_browser_process->clipboard()->WriteObjects(*objects_.get());
  }
