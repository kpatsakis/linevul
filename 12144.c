void InspectorNetworkAgent::DidFinishXHRInternal(ExecutionContext* context,
                                                 XMLHttpRequest* xhr,
                                                 ThreadableLoaderClient* client,
                                                 const AtomicString& method,
                                                 const String& url,
                                                 bool success) {
  ClearPendingRequestData();

  DelayedRemoveReplayXHR(xhr);

  ThreadableLoaderClientRequestIdMap::iterator it =
      known_request_id_map_.find(client);
  if (it == known_request_id_map_.end())
    return;
  known_request_id_map_.erase(client);
}
