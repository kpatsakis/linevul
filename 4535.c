void StoragePartitionImpl::QuotaManagedDataDeletionHelper::ClearDataOnIOThread(
    const scoped_refptr<storage::QuotaManager>& quota_manager,
    const base::Time begin,
    const scoped_refptr<storage::SpecialStoragePolicy>& special_storage_policy,
    const StoragePartition::OriginMatcherFunction& origin_matcher,
    bool perform_storage_cleanup) {
  IncrementTaskCountOnIO();
  base::RepeatingClosure decrement_callback = base::BindRepeating(
      &QuotaManagedDataDeletionHelper::DecrementTaskCountOnIO,
      base::Unretained(this));

  if (quota_storage_remove_mask_ & QUOTA_MANAGED_STORAGE_MASK_PERSISTENT) {
    IncrementTaskCountOnIO();
    quota_manager->GetOriginsModifiedSince(
        blink::mojom::StorageType::kPersistent, begin,
        base::BindOnce(&QuotaManagedDataDeletionHelper::ClearOriginsOnIOThread,
                       base::Unretained(this), base::RetainedRef(quota_manager),
                       special_storage_policy, origin_matcher,
                       perform_storage_cleanup, decrement_callback));
  }

  if (quota_storage_remove_mask_ & QUOTA_MANAGED_STORAGE_MASK_TEMPORARY) {
    IncrementTaskCountOnIO();
    quota_manager->GetOriginsModifiedSince(
        blink::mojom::StorageType::kTemporary, begin,
        base::BindOnce(&QuotaManagedDataDeletionHelper::ClearOriginsOnIOThread,
                       base::Unretained(this), base::RetainedRef(quota_manager),
                       special_storage_policy, origin_matcher,
                       perform_storage_cleanup, decrement_callback));
  }

  if (quota_storage_remove_mask_ & QUOTA_MANAGED_STORAGE_MASK_SYNCABLE) {
    IncrementTaskCountOnIO();
    quota_manager->GetOriginsModifiedSince(
        blink::mojom::StorageType::kSyncable, begin,
        base::BindOnce(&QuotaManagedDataDeletionHelper::ClearOriginsOnIOThread,
                       base::Unretained(this), base::RetainedRef(quota_manager),
                       special_storage_policy, origin_matcher,
                       perform_storage_cleanup, decrement_callback));
  }

  DecrementTaskCountOnIO();
}
