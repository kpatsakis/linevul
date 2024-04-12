void GLES2Implementation::BufferDataHelper(GLenum target,
                                           GLsizeiptr size,
                                           const void* data,
                                           GLenum usage) {
  if (!ValidateSize("glBufferData", size))
    return;

#if defined(MEMORY_SANITIZER) && !defined(OS_NACL)
  if (data)
    __msan_check_mem_is_initialized(data, size);
#endif

  GLuint buffer_id;
  if (GetBoundPixelTransferBuffer(target, "glBufferData", &buffer_id)) {
    if (!buffer_id) {
      return;
    }

    BufferTracker::Buffer* buffer = buffer_tracker_->GetBuffer(buffer_id);
    if (buffer)
      RemoveTransferBuffer(buffer);

    buffer = buffer_tracker_->CreateBuffer(buffer_id, size);
    DCHECK(buffer);
    if (buffer->address() && data)
      memcpy(buffer->address(), data, size);
    return;
  }

  if (IsReadbackUsage(usage)) {
    GLuint id = GetBoundBufferHelper(target);
    readback_buffer_shadow_tracker_->GetOrCreateBuffer(id, size);
  }

  RemoveMappedBufferRangeByTarget(target);

  if (size == 0 || !data) {
    helper_->BufferData(target, size, 0, 0, usage);
    return;
  }

  ScopedTransferBufferPtr buffer(size, helper_, transfer_buffer_);
  if (!buffer.valid()) {
    return;
  }

  if (buffer.size() >= static_cast<unsigned int>(size)) {
    memcpy(buffer.address(), data, size);
    helper_->BufferData(target, size, buffer.shm_id(), buffer.offset(), usage);
    return;
  }

  helper_->BufferData(target, size, 0, 0, usage);
  BufferSubDataHelperImpl(target, 0, size, data, &buffer);
  CheckGLError();
}
