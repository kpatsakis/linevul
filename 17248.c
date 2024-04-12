void PlatformSensorProviderLinux::FreeResources() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  DCHECK(file_task_runner_);
  Shutdown();
  file_task_runner_->PostTask(
      FROM_HERE, base::Bind(&PlatformSensorProviderLinux::StopPollingThread,
                            base::Unretained(this)));
}
