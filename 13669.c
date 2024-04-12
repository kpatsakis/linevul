void DatabaseImpl::IDBThreadHelper::Commit(int64_t transaction_id) {
  DCHECK(idb_thread_checker_.CalledOnValidThread());
  if (!connection_->IsConnected())
    return;

  IndexedDBTransaction* transaction =
      connection_->GetTransaction(transaction_id);
  if (!transaction)
    return;

  if (transaction->size() == 0) {
    connection_->database()->Commit(transaction);
    return;
  }

  indexed_db_context_->quota_manager_proxy()->GetUsageAndQuota(
      indexed_db_context_->TaskRunner(), origin_.GetURL(),
      storage::kStorageTypeTemporary,
      base::Bind(&IDBThreadHelper::OnGotUsageAndQuotaForCommit,
                 weak_factory_.GetWeakPtr(), transaction_id));
}
