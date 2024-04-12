void RenderProcessHostImpl::CreateSharedRendererHistogramAllocator() {
  if (!base::GlobalHistogramAllocator::Get())
    return;

  base::ProcessHandle destination = GetHandle();
  if (destination == base::kNullProcessHandle)
    return;

  if (!metrics_allocator_) {
    std::unique_ptr<base::SharedMemory> shm(new base::SharedMemory());
    if (!shm->CreateAndMapAnonymous(2 << 20))  // 2 MiB
      return;
    metrics_allocator_.reset(new base::SharedPersistentMemoryAllocator(
        std::move(shm), GetID(), "RendererMetrics", /*readonly=*/false));
  }

  base::SharedMemoryHandle shm_handle;
  metrics_allocator_->shared_memory()->ShareToProcess(destination, &shm_handle);
  Send(new ChildProcessMsg_SetHistogramMemory(
      shm_handle, metrics_allocator_->shared_memory()->mapped_size()));
}
