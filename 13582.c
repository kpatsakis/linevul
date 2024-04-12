void ResourceDispatcherHostImpl::UpdateLoadInfo() {
  scoped_ptr<LoadInfoMap> info_map(GetLoadInfoForAllRoutes());

  if (info_map->empty() || !scheduler_->HasLoadingClients()) {
    update_load_states_timer_->Stop();
    return;
  }

  BrowserThread::PostTask(
      BrowserThread::UI, FROM_HERE,
      base::Bind(&ResourceDispatcherHostImpl::UpdateLoadInfoOnUIThread,
                 base::Passed(&info_map)));
}
