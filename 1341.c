void DevToolsAgent::runtimeFeatureStateChanged(
    const WebKit::WebString& feature,
    bool enabled) {
  Send(new DevToolsHostMsg_RuntimePropertyChanged(
      routing_id(),
      feature.utf8(),
      enabled ? "true" : "false"));
}
