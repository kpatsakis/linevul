AwContents::GetMessagePortMessageFilter() {
  if (message_port_message_filter_.get() == nullptr) {
    message_port_message_filter_ =
        new AwMessagePortMessageFilter(
            web_contents_->GetMainFrame()->GetRoutingID());
    web_contents_->GetRenderProcessHost()->AddFilter(
        message_port_message_filter_.get());
  }
  return message_port_message_filter_;
}
