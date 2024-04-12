void SandboxIPCHandler::HandleRequestFromChild(int fd) {
  std::vector<base::ScopedFD> fds;

  char buf[FontConfigIPC::kMaxFontFamilyLength + 128];

  const ssize_t len =
      base::UnixDomainSocket::RecvMsg(fd, buf, sizeof(buf), &fds);
  if (len == -1) {
    NOTREACHED() << "Sandbox host message is larger than kMaxFontFamilyLength";
    return;
  }
  if (fds.empty())
    return;

  base::Pickle pickle(buf, len);
  base::PickleIterator iter(pickle);

  int kind;
  if (!iter.ReadInt(&kind))
    return;

  if (kind == FontConfigIPC::METHOD_MATCH) {
    HandleFontMatchRequest(fd, iter, fds);
  } else if (kind == FontConfigIPC::METHOD_OPEN) {
    HandleFontOpenRequest(fd, iter, fds);
  } else if (kind == LinuxSandbox::METHOD_GET_FALLBACK_FONT_FOR_CHAR) {
    HandleGetFallbackFontForChar(fd, iter, fds);
  } else if (kind == LinuxSandbox::METHOD_LOCALTIME) {
    HandleLocaltime(fd, iter, fds);
  } else if (kind == LinuxSandbox::METHOD_GET_STYLE_FOR_STRIKE) {
    HandleGetStyleForStrike(fd, iter, fds);
  } else if (kind == LinuxSandbox::METHOD_MAKE_SHARED_MEMORY_SEGMENT) {
    HandleMakeSharedMemorySegment(fd, iter, fds);
  } else if (kind == LinuxSandbox::METHOD_MATCH_WITH_FALLBACK) {
    HandleMatchWithFallback(fd, iter, fds);
  }
}
