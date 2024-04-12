static void CloseGpuMemoryBufferHandle(
    const gfx::GpuMemoryBufferHandle& handle) {
  for (const auto& fd : handle.native_pixmap_handle.fds) {
    base::ScopedFD scoped_fd(fd.fd);
  }
}
