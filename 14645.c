void ResourceDispatcherHost::OnCancelRequest(int request_id) {
  CancelRequest(receiver_->id(), request_id, true, true);
}
