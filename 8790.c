void ResourceMessageFilter::OnLaunchNaCl(
    const std::wstring& url, int channel_descriptor, IPC::Message* reply_msg) {
  NaClProcessHost* host = new NaClProcessHost(resource_dispatcher_host_, url);
  host->Launch(this, channel_descriptor, reply_msg);
}
