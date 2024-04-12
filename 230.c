RenderSandboxHostLinux::~RenderSandboxHostLinux() {
  if (init_) {
    if (HANDLE_EINTR(close(renderer_socket_)) < 0)
      PLOG(ERROR) << "close";
    if (HANDLE_EINTR(close(childs_lifeline_fd_)) < 0)
      PLOG(ERROR) << "close";
  }
}
