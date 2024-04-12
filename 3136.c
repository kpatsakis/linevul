void IndexedDBDatabase::Clear(IndexedDBTransaction* transaction,
                              int64_t object_store_id,
                              scoped_refptr<IndexedDBCallbacks> callbacks) {
  DCHECK(transaction);
  IDB_TRACE1("IndexedDBDatabase::Clear", "txn.id", transaction->id());
  DCHECK_NE(transaction->mode(), blink::mojom::IDBTransactionMode::ReadOnly);

  if (!ValidateObjectStoreId(object_store_id))
    return;

  transaction->ScheduleTask(base::BindOnce(&IndexedDBDatabase::ClearOperation,
                                           this, object_store_id, callbacks));
}
