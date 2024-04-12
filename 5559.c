void ResourceDispatcherHostImpl::OnInit() {
  scheduler_.reset(new network::ResourceScheduler(enable_resource_scheduler_));
}
