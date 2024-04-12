void GLES2Implementation::BufferSubData(GLenum target,
                                        GLintptr offset,
                                        GLsizeiptr size,
                                        const void* data) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glBufferSubData("
                     << GLES2Util::GetStringBufferTarget(target) << ", "
                     << offset << ", " << size << ", "
                     << static_cast<const void*>(data) << ")");
  BufferSubDataHelper(target, offset, size, data);
  CheckGLError();
}
