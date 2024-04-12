void ResourceDispatcherHostImpl::RemovePendingRequest(
    const PendingRequestList::iterator& iter) {
  ResourceRequestInfoImpl* info =
      ResourceRequestInfoImpl::ForRequest(iter->second);

  IncrementOutstandingRequestsMemoryCost(-1 * info->memory_cost(),
                                         info->GetChildID());

  if (info->login_delegate())
    info->login_delegate()->OnRequestCancelled();
  if (info->ssl_client_auth_handler())
    info->ssl_client_auth_handler()->OnRequestCancelled();
  transferred_navigations_.erase(
      GlobalRequestID(info->GetChildID(), info->GetRequestID()));

  delete iter->second;
  pending_requests_.erase(iter);

  if (pending_requests_.empty() && update_load_states_timer_.get())
    update_load_states_timer_->Stop();
}
