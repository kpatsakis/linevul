bool GpuDataManager::RemoveGpuInfoUpdateCallback(Callback0::Type* callback) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  std::set<Callback0::Type*>::iterator i =
      gpu_info_update_callbacks_.find(callback);
  if (i != gpu_info_update_callbacks_.end()) {
    gpu_info_update_callbacks_.erase(i);
    return true;
  }
  return false;
}
