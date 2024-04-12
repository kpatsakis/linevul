HttpBridgeFactory::HttpBridgeFactory(
    net::URLRequestContextGetter* baseline_context_getter) {
  DCHECK(baseline_context_getter != NULL);
  request_context_getter_ =
      new HttpBridge::RequestContextGetter(baseline_context_getter);
}
