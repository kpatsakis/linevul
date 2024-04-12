sync_api::HttpPostProviderInterface* HttpBridgeFactory::Create() {
  HttpBridge* http = new HttpBridge(request_context_getter_);
  http->AddRef();
  return http;
}
