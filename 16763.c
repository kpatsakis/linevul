RenderProcessHost* RenderProcessHostImpl::CreateRenderProcessHost(
    BrowserContext* browser_context,
    StoragePartitionImpl* storage_partition_impl,
    SiteInstance* site_instance,
    bool is_for_guests_only) {
  if (g_render_process_host_factory_) {
    return g_render_process_host_factory_->CreateRenderProcessHost(
        browser_context, site_instance);
  }

  if (!storage_partition_impl) {
    storage_partition_impl = static_cast<StoragePartitionImpl*>(
        BrowserContext::GetStoragePartition(browser_context, site_instance));
  }
  if (is_for_guests_only && site_instance &&
      storage_partition_impl->site_for_service_worker().is_empty()) {
    storage_partition_impl->set_site_for_service_worker(
        site_instance->GetSiteURL());
  }

  return new RenderProcessHostImpl(browser_context, storage_partition_impl,
                                   is_for_guests_only);
}
