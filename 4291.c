void InspectorNetworkAgent::DidChangeResourcePriority(
    unsigned long identifier,
    ResourceLoadPriority load_priority) {
  String request_id = IdentifiersFactory::RequestId(identifier);
  GetFrontend()->resourceChangedPriority(request_id,
                                         ResourcePriorityJSON(load_priority),
                                         MonotonicallyIncreasingTime());
}
