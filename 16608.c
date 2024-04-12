StoragePartitionImpl::GetURLLoaderFactoryForBrowserProcessIOThread() {
  return url_loader_factory_getter_->GetNetworkFactoryInfo();
}
