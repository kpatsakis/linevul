void InspectorNetworkAgent::DidReceiveData(unsigned long identifier,
                                           DocumentLoader* loader,
                                           const char* data,
                                           int data_length) {
  String request_id = IdentifiersFactory::RequestId(identifier);

  if (data) {
    NetworkResourcesData::ResourceData const* resource_data =
        resources_data_->Data(request_id);
    if (resource_data &&
        (!resource_data->CachedResource() ||
         resource_data->CachedResource()->GetDataBufferingPolicy() ==
             kDoNotBufferData ||
         IsErrorStatusCode(resource_data->HttpStatusCode())))
      resources_data_->MaybeAddResourceData(request_id, data, data_length);
  }

  GetFrontend()->dataReceived(
      request_id, MonotonicallyIncreasingTime(), data_length,
      resources_data_->GetAndClearPendingEncodedDataLength(request_id));
}
