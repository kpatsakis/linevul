void StorageHandler::NotifyCacheStorageContentChanged(const std::string& origin,
                                                      const std::string& name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  frontend_->CacheStorageContentUpdated(origin, name);
}
