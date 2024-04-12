bool Syncer::ExitRequested() {
  base::AutoLock lock(early_exit_requested_lock_);
  return early_exit_requested_;
}
