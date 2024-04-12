int32_t CommandBufferProxyImpl::CreateImage(ClientBuffer buffer,
                                            size_t width,
                                            size_t height,
                                            unsigned internal_format) {
  CheckLock();
  base::AutoLock lock(last_state_lock_);
  if (last_state_.error != gpu::error::kNoError)
    return -1;

  int32_t new_id = channel_->ReserveImageId();

  gfx::GpuMemoryBuffer* gpu_memory_buffer =
      reinterpret_cast<gfx::GpuMemoryBuffer*>(buffer);
  DCHECK(gpu_memory_buffer);

  gfx::GpuMemoryBufferHandle handle =
      gfx::CloneHandleForIPC(gpu_memory_buffer->GetHandle());
  bool requires_sync_token = handle.type == gfx::IO_SURFACE_BUFFER;

  uint64_t image_fence_sync = 0;
  if (requires_sync_token) {
    image_fence_sync = GenerateFenceSyncRelease();

    DCHECK_EQ(image_fence_sync, flushed_fence_sync_release_ + 1);
  }

  DCHECK(gpu::IsImageFromGpuMemoryBufferFormatSupported(
      gpu_memory_buffer->GetFormat(), capabilities_));
  DCHECK(gpu::IsImageSizeValidForGpuMemoryBufferFormat(
      gfx::Size(width, height), gpu_memory_buffer->GetFormat()));
  DCHECK(gpu::IsImageFormatCompatibleWithGpuMemoryBufferFormat(
      internal_format, gpu_memory_buffer->GetFormat()));

  GpuCommandBufferMsg_CreateImage_Params params;
  params.id = new_id;
  params.gpu_memory_buffer = handle;
  params.size = gfx::Size(width, height);
  params.format = gpu_memory_buffer->GetFormat();
  params.internal_format = internal_format;
  params.image_release_count = image_fence_sync;

  Send(new GpuCommandBufferMsg_CreateImage(route_id_, params));

  if (image_fence_sync) {
    gpu::SyncToken sync_token(GetNamespaceID(), GetCommandBufferID(),
                              image_fence_sync);

    EnsureWorkVisible();
    sync_token.SetVerifyFlush();

    gpu_memory_buffer_manager_->SetDestructionSyncToken(gpu_memory_buffer,
                                                        sync_token);
  }

  return new_id;
}
