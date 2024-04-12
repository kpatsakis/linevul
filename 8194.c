void GpuCommandBufferStub::OnDestroyTransferBuffer(
    int32 id,
    IPC::Message* reply_message) {
  TRACE_EVENT0("gpu", "GpuCommandBufferStub::OnDestroyTransferBuffer");
  if (command_buffer_.get()) {
    command_buffer_->DestroyTransferBuffer(id);
  } else {
    reply_message->set_reply_error();
  }
  Send(reply_message);
}
