void* GLES2Implementation::MapBufferSubDataCHROMIUM(GLuint target,
                                                    GLintptr offset,
                                                    GLsizeiptr size,
                                                    GLenum access) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glMapBufferSubDataCHROMIUM("
                     << target << ", " << offset << ", " << size << ", "
                     << GLES2Util::GetStringEnum(access) << ")");
  if (access != GL_WRITE_ONLY) {
    SetGLErrorInvalidEnum("glMapBufferSubDataCHROMIUM", access, "access");
    return nullptr;
  }
  if (!ValidateSize("glMapBufferSubDataCHROMIUM", size) ||
      !ValidateOffset("glMapBufferSubDataCHROMIUM", offset)) {
    return nullptr;
  }

  int32_t shm_id;
  unsigned int shm_offset;
  void* mem = mapped_memory_->Alloc(size, &shm_id, &shm_offset);
  if (!mem) {
    SetGLError(GL_OUT_OF_MEMORY, "glMapBufferSubDataCHROMIUM", "out of memory");
    return nullptr;
  }

  std::pair<MappedBufferMap::iterator, bool> result = mapped_buffers_.insert(
      std::make_pair(mem, MappedBuffer(access, shm_id, mem, shm_offset, target,
                                       offset, size)));
  DCHECK(result.second);
  GPU_CLIENT_LOG("  returned " << mem);
  return mem;
}
