void WebGraphicsContext3DCommandBufferImpl::OnMemoryAllocationChanged(
    const GpuMemoryAllocation& allocation) {
  if (memory_allocation_changed_callback_)
    memory_allocation_changed_callback_->onMemoryAllocationChanged(
        allocation.gpu_resource_size_in_bytes);
}
