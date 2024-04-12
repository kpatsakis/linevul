void ResourceDispatcherHostImpl::OnRenderViewHostCreated(int child_id,
                                                         int route_id) {
  scheduler_->OnClientCreated(child_id, route_id);
}
