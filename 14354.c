RenderThreadImpl::HostAllocateSharedMemoryBuffer(size_t size) {
  return ChildThreadImpl::AllocateSharedMemory(size);
}
