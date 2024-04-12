void GpuCommandBufferStub::OnEcho(const IPC::Message& message) {
  TRACE_EVENT0("gpu", "GpuCommandBufferStub::OnEcho");
  Send(new IPC::Message(message));
}
