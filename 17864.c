 void ResourceDispatcherHostImpl::UpdateRequestForTransfer(
     int child_id,
     int route_id,
    int request_id,
    const ResourceHostMsg_Request& request_data,
    LoaderMap::iterator iter) {
  ResourceRequestInfoImpl* info = iter->second->GetRequestInfo();
  GlobalRoutingID old_routing_id(
      request_data.transferred_request_child_id, info->GetRouteID());
  GlobalRequestID old_request_id(request_data.transferred_request_child_id,
                                 request_data.transferred_request_request_id);
  GlobalRoutingID new_routing_id(child_id, route_id);
  GlobalRequestID new_request_id(child_id, request_id);

  IncrementOutstandingRequestsMemory(-1, *info);
  bool should_update_count = info->counted_as_in_flight_request();
  if (should_update_count)
    IncrementOutstandingRequestsCount(-1, info);

  DCHECK(pending_loaders_.find(old_request_id) == iter);
  scoped_ptr<ResourceLoader> loader = std::move(iter->second);
  ResourceLoader* loader_ptr = loader.get();
  pending_loaders_.erase(iter);

  info->UpdateForTransfer(child_id, route_id, request_data.render_frame_id,
                          request_data.origin_pid, request_id,
                          filter_->GetWeakPtr());

  pending_loaders_[new_request_id] = std::move(loader);
  IncrementOutstandingRequestsMemory(1, *info);
  if (should_update_count)
    IncrementOutstandingRequestsCount(1, info);
  if (old_routing_id != new_routing_id) {
    if (blocked_loaders_map_.find(old_routing_id) !=
            blocked_loaders_map_.end()) {
      blocked_loaders_map_[new_routing_id] =
          std::move(blocked_loaders_map_[old_routing_id]);
      blocked_loaders_map_.erase(old_routing_id);
    }
  }
  if (old_request_id != new_request_id) {
    DelegateMap::iterator it = delegate_map_.find(old_request_id);
    if (it != delegate_map_.end()) {
      base::ObserverList<ResourceMessageDelegate>::Iterator del_it(it->second);
      ResourceMessageDelegate* delegate;
      while ((delegate = del_it.GetNext()) != NULL) {
        delegate->set_request_id(new_request_id);
      }
      delegate_map_[new_request_id] = delegate_map_[old_request_id];
      delegate_map_.erase(old_request_id);
    }
  }

  AppCacheInterceptor::CompleteCrossSiteTransfer(
      loader_ptr->request(),
      child_id,
      request_data.appcache_host_id,
      filter_);

  ServiceWorkerRequestHandler* handler =
      ServiceWorkerRequestHandler::GetHandler(loader_ptr->request());
  if (handler) {
    if (!handler->SanityCheckIsSameContext(filter_->service_worker_context())) {
      bad_message::ReceivedBadMessage(
          filter_, bad_message::RDHI_WRONG_STORAGE_PARTITION);
    } else {
      handler->CompleteCrossSiteTransfer(
          child_id, request_data.service_worker_provider_id);
    }
  }

  DCHECK(info->cross_site_handler());
}
