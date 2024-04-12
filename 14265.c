void ResourceDispatcherHostImpl::DataReceivedACK(int child_id,
                                                 int request_id) {
  PendingRequestList::iterator i = pending_requests_.find(
      GlobalRequestID(child_id, request_id));
  if (i == pending_requests_.end())
    return;

  ResourceRequestInfoImpl* info =
      ResourceRequestInfoImpl::ForRequest(i->second);

  info->DecrementPendingDataCount();

  if (info->pending_data_count() == kMaxPendingDataMessages) {
    info->DecrementPendingDataCount();

    PauseRequest(child_id, request_id, false);
  }
}
