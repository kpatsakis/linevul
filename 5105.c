void CommandBufferProxyImpl::DestroyImage(int32_t id) {
  CheckLock();
  base::AutoLock lock(last_state_lock_);
  if (last_state_.error != gpu::error::kNoError)
    return;

  Send(new GpuCommandBufferMsg_DestroyImage(route_id_, id));
}
