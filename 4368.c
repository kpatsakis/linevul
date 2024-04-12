void ResourceDispatcherHostImpl::BlockRequestsForRoute(
    const GlobalFrameRoutingId& global_routing_id) {
  DCHECK(io_thread_task_runner_->BelongsToCurrentThread());
  DCHECK(blocked_loaders_map_.find(global_routing_id) ==
         blocked_loaders_map_.end())
      << "BlockRequestsForRoute called  multiple time for the same RFH";
  blocked_loaders_map_[global_routing_id] =
      std::make_unique<BlockedLoadersList>();
}
