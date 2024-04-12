void ResourceFetcher::HandleLoaderFinish(Resource* resource,
                                         double finish_time,
                                         LoaderFinishType type) {
  DCHECK(resource);

  ResourceLoader* loader = resource->Loader();
  if (type == kDidFinishFirstPartInMultipart) {
    MoveResourceLoaderToNonBlocking(loader);
  } else {
    RemoveResourceLoader(loader);
    DCHECK(!non_blocking_loaders_.Contains(loader));
  }
  DCHECK(!loaders_.Contains(loader));

  const int64_t encoded_data_length =
      resource->GetResponse().EncodedDataLength();

  if (resource->GetType() == Resource::kMainResource) {
    DCHECK(navigation_timing_info_);
    AddRedirectsToTimingInfo(resource, navigation_timing_info_.Get());
    if (resource->GetResponse().IsHTTP()) {
      PopulateTimingInfo(navigation_timing_info_.Get(), resource);
      navigation_timing_info_->AddFinalTransferSize(
          encoded_data_length == -1 ? 0 : encoded_data_length);
    }
  }
  if (RefPtr<ResourceTimingInfo> info =
          resource_timing_info_map_.Take(resource)) {
    AddRedirectsToTimingInfo(resource, info.Get());

    if (resource->GetResponse().IsHTTP() &&
        resource->GetResponse().HttpStatusCode() < 400) {
      PopulateTimingInfo(info.Get(), resource);
      info->SetLoadFinishTime(finish_time);
      info->AddFinalTransferSize(
          encoded_data_length == -1 ? 0 : encoded_data_length);

      if (resource->Options().request_initiator_context == kDocumentContext)
        Context().AddResourceTiming(*info);
      resource->ReportResourceTimingToClients(*info);
    }
  }

  Context().DispatchDidFinishLoading(
      resource->Identifier(), finish_time, encoded_data_length,
      resource->GetResponse().DecodedBodyLength());

  if (type == kDidFinishLoading)
    resource->Finish(finish_time);

  HandleLoadCompletion(resource);
}
