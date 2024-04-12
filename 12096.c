void IndexedDBDatabase::DeleteRange(
    IndexedDBTransaction* transaction,
    int64_t object_store_id,
    std::unique_ptr<IndexedDBKeyRange> key_range,
    scoped_refptr<IndexedDBCallbacks> callbacks) {
  DCHECK(transaction);
  IDB_TRACE1("IndexedDBDatabase::DeleteRange", "txn.id", transaction->id());
  DCHECK_NE(transaction->mode(), blink::mojom::IDBTransactionMode::ReadOnly);

  if (!ValidateObjectStoreId(object_store_id))
    return;

  transaction->ScheduleTask(
      base::BindOnce(&IndexedDBDatabase::DeleteRangeOperation, this,
                     object_store_id, std::move(key_range), callbacks));
}
