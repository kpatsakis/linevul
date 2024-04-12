void CommandBufferProxyImpl::OnGpuAsyncMessageError(
    gpu::error::ContextLostReason reason,
    gpu::error::Error error) {
  CheckLock();
  last_state_lock_.AssertAcquired();
  last_state_.error = error;
  last_state_.context_lost_reason = reason;
  base::AutoUnlock unlock(last_state_lock_);
  DisconnectChannel();
}
