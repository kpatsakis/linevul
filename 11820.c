void FileAPIMessageFilter::BadMessageReceived() {
  RecordAction(UserMetricsAction("BadMessageTerminate_FAMF"));
  BrowserMessageFilter::BadMessageReceived();
}
