void DevToolsAgent::runtimePropertyChanged(
    const WebKit::WebString& name,
    const WebKit::WebString& value) {
  Send(new DevToolsHostMsg_RuntimePropertyChanged(
      routing_id(),
      name.utf8(),
      value.utf8()));
}
