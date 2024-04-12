void GpuProcessHost::AddFilter(IPC::ChannelProxy::MessageFilter* filter) {
  DCHECK(CalledOnValidThread());
  process_->GetHost()->AddFilter(filter);
}
