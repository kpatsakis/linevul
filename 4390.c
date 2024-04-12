Channel::ChannelImpl::ChannelImpl(const std::string& channel_id, Mode mode,
                                  Listener* listener)
    : mode_(mode),
      is_blocked_on_write_(false),
      message_send_bytes_written_(0),
      uses_fifo_(CommandLine::ForCurrentProcess()->HasSwitch(
                     switches::kIPCUseFIFO)),
      server_listen_pipe_(-1),
      pipe_(-1),
      client_pipe_(-1),
#if !defined(OS_MACOSX)
      fd_pipe_(-1),
      remote_fd_pipe_(-1),
#endif
      listener_(listener),
      waiting_connect_(true),
      factory_(this) {
  if (!CreatePipe(channel_id, mode)) {
    PLOG(WARNING) << "Unable to create pipe named \"" << channel_id
                  << "\" in " << (mode == MODE_SERVER ? "server" : "client")
                  << " mode";
  }
}
