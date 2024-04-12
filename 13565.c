IPC::Message* ExecuteBrowserCommandObserver::ReleaseReply() {
  return reply_message_.release();
}
