  bool Send(IPC::Message* message) {
    return channel_->Send(message);
  }
