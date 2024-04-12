  virtual ~SwichToMetroUIHandler() {
    default_browser_worker_->ObserverDestroyed();
  }
