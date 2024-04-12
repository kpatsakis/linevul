ChildThread::ChildThread()
    : router_(this),
      channel_connected_factory_(this),
      in_browser_process_(false) {
  channel_name_ = CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
      switches::kProcessChannelID);
  Init();
}
