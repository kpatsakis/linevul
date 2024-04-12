void BrowserPpapiHostImpl::OnThrottleStateChanged(PP_Instance instance,
                                                  bool is_throttled) {
  auto it = instance_map_.find(instance);
  if (it != instance_map_.end()) {
    it->second->is_throttled = is_throttled;
    for (auto& observer : it->second->observer_list)
      observer.OnThrottleStateChanged(is_throttled);
  }
}
