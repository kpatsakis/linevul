void DatabaseImpl::IDBThreadHelper::RenameObjectStore(
    int64_t transaction_id,
    int64_t object_store_id,
    const base::string16& new_name) {
  DCHECK(idb_thread_checker_.CalledOnValidThread());
  if (!connection_->IsConnected())
    return;

  IndexedDBTransaction* transaction =
      connection_->GetTransaction(transaction_id);
  if (!transaction)
    return;

  connection_->database()->RenameObjectStore(transaction, object_store_id,
                                             new_name);
}
