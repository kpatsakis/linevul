  void ReceiverReady(IPC::Channel::Sender* sender) {
    has_receiver_ = true;
    Update(sender);
  }
