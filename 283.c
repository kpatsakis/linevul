bool WebPluginImpl::handleInputEvent(
    const WebInputEvent& event, WebCursorInfo& cursor_info) {
  return delegate_->HandleInputEvent(event, &cursor_info);
}
