  void ResetMonitoredUrls() {
    base::AutoLock lock(lock_);
    monitored_urls_.clear();
  }
