void ResourceDispatcherHostImpl::CancelRequest(int child_id,
                                               int request_id,
                                               bool from_renderer) {
  if (from_renderer) {
    if (IsTransferredNavigation(GlobalRequestID(child_id, request_id)))
      return;
  }

  ResourceLoader* loader = GetLoader(child_id, request_id);
  if (!loader) {
    DVLOG(1) << "Canceling a request that wasn't found";
    return;
  }

  loader->CancelRequest(from_renderer);
}
