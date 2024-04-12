ChildThread::ChildThread(const std::string& channel_name)
    : channel_name_(channel_name),
      router_(this),
      channel_connected_factory_(this),
      in_browser_process_(true) {
  Init();
}
