Status IndexedDBDatabase::CountOperation(
    int64_t object_store_id,
    int64_t index_id,
    std::unique_ptr<IndexedDBKeyRange> key_range,
    scoped_refptr<IndexedDBCallbacks> callbacks,
    IndexedDBTransaction* transaction) {
  IDB_TRACE1("IndexedDBDatabase::CountOperation", "txn.id", transaction->id());
  uint32_t count = 0;
  std::unique_ptr<IndexedDBBackingStore::Cursor> backing_store_cursor;

  Status s = Status::OK();
  if (index_id == IndexedDBIndexMetadata::kInvalidId) {
    backing_store_cursor = backing_store_->OpenObjectStoreKeyCursor(
        transaction->BackingStoreTransaction(), id(), object_store_id,
        *key_range, blink::kWebIDBCursorDirectionNext, &s);
  } else {
    backing_store_cursor = backing_store_->OpenIndexKeyCursor(
        transaction->BackingStoreTransaction(), id(), object_store_id, index_id,
        *key_range, blink::kWebIDBCursorDirectionNext, &s);
  }
  if (!s.ok()) {
    DLOG(ERROR) << "Unable perform count operation: " << s.ToString();
    return s;
  }
  if (!backing_store_cursor) {
    callbacks->OnSuccess(count);
    return s;
  }

  do {
    if (!s.ok())
      return s;
    ++count;
  } while (backing_store_cursor->Continue(&s));

  callbacks->OnSuccess(count);
  return s;
}
