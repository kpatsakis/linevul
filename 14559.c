void OfflinePageModelImpl::PostClearStorageIfNeededTask(bool delayed) {
  base::TimeDelta delay =
      delayed ? kStorageManagerStartingDelay : base::TimeDelta();
  base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
      FROM_HERE, base::Bind(&OfflinePageModelImpl::ClearStorageIfNeeded,
                            weak_ptr_factory_.GetWeakPtr(),
                            base::Bind(&OfflinePageModelImpl::OnStorageCleared,
                                       weak_ptr_factory_.GetWeakPtr())),
      delay);
}
