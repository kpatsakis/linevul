void ResourceDispatcherHostImpl::OnCancelRequest(int request_id) {
  CancelRequest(filter_->child_id(), request_id, true);
}
