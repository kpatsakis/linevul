  void SetStatusCode(net::HttpStatusCode status_code) {
    base::AutoLock auto_lock(lock_);
    status_code_ = status_code;
  }
