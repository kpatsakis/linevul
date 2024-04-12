void RenderFrameHostManager::OnEnforceInsecureNavigationsSet(
    const std::vector<uint32_t>& insecure_navigations_set) {
  for (const auto& pair : proxy_hosts_) {
    pair.second->Send(new FrameMsg_EnforceInsecureNavigationsSet(
        pair.second->GetRoutingID(), insecure_navigations_set));
  }
}
