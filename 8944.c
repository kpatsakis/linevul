void DevToolsAgent::OnDispatchOnInspectorBackend(const std::string& message) {
  WebDevToolsAgent* web_agent = GetWebAgent();
  if (web_agent)
    web_agent->dispatchOnInspectorBackend(WebString::fromUTF8(message));
}
