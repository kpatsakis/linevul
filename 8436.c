void ResourceDispatcherHostImpl::EnableStaleWhileRevalidateForTesting() {
  if (!async_revalidation_manager_)
    async_revalidation_manager_.reset(new AsyncRevalidationManager);
}
