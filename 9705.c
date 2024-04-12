bool CommandBufferProxyImpl::Send(IPC::Message* msg) {
  DCHECK(last_state_.error == gpu::error::kNoError);

  if (channel_) {
    if (channel_->Send(msg)) {
      return true;
    } else {
      last_state_.error = gpu::error::kLostContext;
      return false;
    }
  }

  delete msg;
  return false;
}
