void GpuCommandBufferStub::OnCommandProcessed() {
  if (watchdog_)
    watchdog_->CheckArmed();
}
