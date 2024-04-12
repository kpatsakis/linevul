bool CommandBufferProxyImpl::EnsureBackbuffer() {
  if (last_state_.error != gpu::error::kNoError)
    return false;

  return Send(new GpuCommandBufferMsg_EnsureBackbuffer(route_id_));
}
