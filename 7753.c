void CreateMemoryCoordinatorHandleForGpuProcess(
    int gpu_process_id,
    mojom::MemoryCoordinatorHandleRequest request) {
  MemoryCoordinatorImpl::GetInstance()->CreateHandle(gpu_process_id,
                                                     std::move(request));
}
