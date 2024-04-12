bool NaClProcessHost::Send(IPC::Message* msg) {
  return process_->Send(msg);
}
