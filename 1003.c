void IndexedDBDatabase::GetKeyGeneratorCurrentNumber(
    IndexedDBTransaction* transaction,
    int64_t object_store_id,
    scoped_refptr<IndexedDBCallbacks> callbacks) {
  DCHECK(transaction);
  if (!ValidateObjectStoreId(object_store_id)) {
    callbacks->OnError(CreateError(blink::kWebIDBDatabaseExceptionDataError,
                                   "Object store id not valid.", transaction));
    return;
  }
  transaction->ScheduleTask(
      base::BindOnce(&IndexedDBDatabase::GetKeyGeneratorCurrentNumberOperation,
                     this, object_store_id, callbacks));
}
