void SandboxIPCHandler::HandleFontOpenRequest(
    int fd,
    base::PickleIterator iter,
    const std::vector<base::ScopedFD>& fds) {
  uint32_t index;
  if (!iter.ReadUInt32(&index))
    return;
  if (index >= static_cast<uint32_t>(paths_.size()))
    return;
  if (g_test_observer) {
    g_test_observer->OnFontOpen(index);
  }
  const int result_fd = open(paths_[index].c_str(), O_RDONLY);

  base::Pickle reply;
  reply.WriteBool(result_fd != -1);

  SendRendererReply(fds, reply, result_fd);

  if (result_fd >= 0) {
    int err = IGNORE_EINTR(close(result_fd));
    DCHECK(!err);
  }
}
