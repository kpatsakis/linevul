  static void ResetMonitor() {
    NetworkActivityMonitor* monitor = NetworkActivityMonitor::GetInstance();
    base::AutoLock lock(monitor->lock_);
    monitor->bytes_sent_ = 0;
    monitor->bytes_received_ = 0;
    monitor->last_received_ticks_ = base::TimeTicks();
    monitor->last_sent_ticks_ = base::TimeTicks();
  }
