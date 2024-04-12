void ResourceDispatcherHostImpl::OnUploadProgressACK(int request_id) {
  int child_id = filter_->child_id();
  PendingRequestList::iterator i = pending_requests_.find(
      GlobalRequestID(child_id, request_id));
  if (i == pending_requests_.end())
    return;

  ResourceRequestInfoImpl* info =
      ResourceRequestInfoImpl::ForRequest(i->second);
  info->set_waiting_for_upload_progress_ack(false);
}
