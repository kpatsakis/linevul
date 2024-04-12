void DevToolsSession::AttachToAgent(
    const blink::mojom::DevToolsAgentAssociatedPtr& agent) {
  blink::mojom::DevToolsSessionHostAssociatedPtrInfo host_ptr_info;
  binding_.Bind(mojo::MakeRequest(&host_ptr_info));
  agent->AttachDevToolsSession(
      std::move(host_ptr_info), mojo::MakeRequest(&session_ptr_),
      mojo::MakeRequest(&io_session_ptr_), state_cookie_);
  session_ptr_.set_connection_error_handler(base::BindOnce(
      &DevToolsSession::MojoConnectionDestroyed, base::Unretained(this)));

  if (!suspended_sending_messages_to_agent_) {
    for (const auto& pair : waiting_for_response_messages_) {
      int call_id = pair.first;
      const WaitingMessage& message = pair.second;
      DispatchProtocolMessageToAgent(call_id, message.method, message.message);
    }
  } else {
    std::vector<SuspendedMessage> temp;
    for (const auto& pair : waiting_for_response_messages_)
      temp.push_back({pair.first, pair.second.method, pair.second.message});
    suspended_messages_.insert(suspended_messages_.begin(), temp.begin(),
                               temp.end());
    waiting_for_response_messages_.clear();
  }

  if (!state_cookie_.has_value())
    state_cookie_ = std::string();
}
