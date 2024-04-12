void ResourceDispatcherHostImpl::ClearLoginDelegateForRequest(
    net::URLRequest* request) {
  ResourceRequestInfoImpl* info = ResourceRequestInfoImpl::ForRequest(request);
  if (info) {
    ResourceLoader* loader = GetLoader(info->GetGlobalRequestID());
    if (loader)
      loader->ClearLoginDelegate();
  }
}
