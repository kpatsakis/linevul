void RendererSchedulerImpl::SetVirtualTimeStopped(bool virtual_time_stopped) {
  if (main_thread_only().virtual_time_stopped == virtual_time_stopped)
    return;
  main_thread_only().virtual_time_stopped = virtual_time_stopped;

  if (!main_thread_only().use_virtual_time)
    return;

  virtual_time_domain_->SetCanAdvanceVirtualTime(!virtual_time_stopped);

  if (virtual_time_stopped) {
    VirtualTimePaused();
  } else {
    VirtualTimeResumed();
  }
}
