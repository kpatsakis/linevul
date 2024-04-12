void ResourceDispatcherHostImpl::MarkAsTransferredNavigation(
    net::URLRequest* transferred_request) {
  ResourceRequestInfoImpl* info =
      ResourceRequestInfoImpl::ForRequest(transferred_request);

  GlobalRequestID transferred_request_id(info->GetChildID(),
                                         info->GetRequestID());
  transferred_navigations_[transferred_request_id] = transferred_request;

  scoped_refptr<ResourceHandler> transferred_resource_handler(
      new DoomedResourceHandler(info->resource_handler()));
  info->set_resource_handler(transferred_resource_handler.get());
}
