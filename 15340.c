void CloseFds(const std::vector<int>& fds) {
  for (const auto& it : fds) {
    PCHECK(0 == IGNORE_EINTR(close(it)));
  }
}
