IPC::Message* AutomationProviderBookmarkModelObserver::ReleaseReply() {
  return reply_message_.release();
}
