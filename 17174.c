void DevToolsSession::DispatchProtocolNotification(const std::string& message) {
  client_->DispatchProtocolMessage(agent_host_, message);
}
