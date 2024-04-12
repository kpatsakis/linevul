void Dispatcher::OnDeliverMessage(int target_port_id, const Message& message) {
  scoped_ptr<RequestSender::ScopedTabID> scoped_tab_id;
  std::map<int, int>::const_iterator it =
      port_to_tab_id_map_.find(target_port_id);
  if (it != port_to_tab_id_map_.end()) {
    scoped_tab_id.reset(
        new RequestSender::ScopedTabID(request_sender(), it->second));
  }

  MessagingBindings::DeliverMessage(*script_context_set_, target_port_id,
                                    message,
                                    NULL);  // All render frames.
}
