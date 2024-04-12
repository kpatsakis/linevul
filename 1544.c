void Syncer::RequestEarlyExit() {
  base::AutoLock lock(early_exit_requested_lock_);
  early_exit_requested_ = true;
}
