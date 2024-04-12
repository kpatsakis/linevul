void RenderFrameHostManager::OnDidStartLoading() {
  for (const auto& pair : proxy_hosts_) {
    pair.second->Send(
        new FrameMsg_DidStartLoading(pair.second->GetRoutingID()));
  }
}
