void QuotaManager::GetUsageAndQuotaForEviction(
    const GetUsageAndQuotaForEvictionCallback& callback) {
  DCHECK(io_thread_->BelongsToCurrentThread());
  GetUsageAndQuotaInternal(
      GURL(), kStorageTypeTemporary, true /* global */, callback);
}
