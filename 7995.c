void CommandBufferProxyImpl::OrderingBarrier(int32_t put_offset) {
  CheckLock();
  base::AutoLock lock(last_state_lock_);
  if (last_state_.error != gpu::error::kNoError)
    return;

  TRACE_EVENT1("gpu", "CommandBufferProxyImpl::OrderingBarrier", "put_offset",
               put_offset);

  OrderingBarrierHelper(put_offset);
}
