void GpuChannelHost::MessageFilter::AddRoute(
    int route_id,
    base::WeakPtr<IPC::Channel::Listener> listener,
    scoped_refptr<MessageLoopProxy> loop) {
  DCHECK(parent_->factory_->IsIOThread());
  DCHECK(listeners_.find(route_id) == listeners_.end());
  GpuListenerInfo info;
  info.listener = listener;
  info.loop = loop;
  listeners_[route_id] = info;
}
