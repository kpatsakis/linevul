bool BrowserRenderProcessHost::Send(IPC::Message* msg) {
  if (!channel_.get()) {
    delete msg;
    return false;
  }
  return channel_->Send(msg);
}
