void DevToolsAgentHostImpl::NotifyCreated() {
  DCHECK(g_devtools_instances.Get().find(id_) ==
         g_devtools_instances.Get().end());
  g_devtools_instances.Get()[id_] = this;
  for (auto& observer : g_devtools_observers.Get())
    observer.DevToolsAgentHostCreated(this);
}
