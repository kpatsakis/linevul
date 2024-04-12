void MockRenderThread::RemoveFilter(IPC::ChannelProxy::MessageFilter* filter) {
  filter->OnFilterRemoved();
}
