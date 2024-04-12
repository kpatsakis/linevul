void GpuCommandBufferStub::OnSetClientHasMemoryAllocationChangedCallback(
    bool has_callback) {
  TRACE_EVENT0(
      "gpu",
      "GpuCommandBufferStub::OnSetClientHasMemoryAllocationChangedCallback");
  if (has_callback) {
    GetMemoryManager()->AddClient(
        this,
        surface_id_ != 0,
        true,
        base::TimeTicks::Now());
  } else {
    GetMemoryManager()->RemoveClient(
        this);
  }
}
