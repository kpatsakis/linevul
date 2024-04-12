void DevToolsAgentFilter::OnDispatchOnInspectorBackend(
    const std::string& message) {
  if (!WebDevToolsAgent::shouldInterruptForMessage(
          WebString::fromUTF8(message))) {
      message_handled_ = false;
      return;
  }
  WebDevToolsAgent::interruptAndDispatch(
      new MessageImpl(message, current_routing_id_));

  render_thread_loop_->PostTask(
      FROM_HERE,
      NewRunnableFunction(&WebDevToolsAgent::processPendingMessages));
}
