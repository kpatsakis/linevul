std::vector<NetworkHandler*> NetworkHandler::ForAgentHost(
    DevToolsAgentHostImpl* host) {
  return DevToolsSession::HandlersForAgentHost<NetworkHandler>(
      host, Network::Metainfo::domainName);
}
