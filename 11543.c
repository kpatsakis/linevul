void PlatformSensorProviderLinux::StopPollingThread() {
  DCHECK(file_task_runner_);
  DCHECK(file_task_runner_->BelongsToCurrentThread());
  if (polling_thread_ && polling_thread_->IsRunning())
    polling_thread_->Stop();
}
