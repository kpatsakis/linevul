void IndexedDBDatabase::CreateObjectStore(IndexedDBTransaction* transaction,
                                          int64_t object_store_id,
                                          const base::string16& name,
                                          const IndexedDBKeyPath& key_path,
                                          bool auto_increment) {
  DCHECK(transaction);
  IDB_TRACE1("IndexedDBDatabase::CreateObjectStore", "txn.id",
             transaction->id());
  DCHECK_EQ(transaction->mode(), blink::kWebIDBTransactionModeVersionChange);

  if (base::ContainsKey(metadata_.object_stores, object_store_id)) {
    DLOG(ERROR) << "Invalid object_store_id";
    return;
  }

  UMA_HISTOGRAM_ENUMERATION("WebCore.IndexedDB.Schema.ObjectStore.KeyPathType",
                            HistogramKeyPathType(key_path), KEY_PATH_TYPE_MAX);
  UMA_HISTOGRAM_BOOLEAN("WebCore.IndexedDB.Schema.ObjectStore.AutoIncrement",
                        auto_increment);

  IndexedDBObjectStoreMetadata object_store_metadata;
  Status s = metadata_coding_->CreateObjectStore(
      transaction->BackingStoreTransaction()->transaction(),
      transaction->database()->id(), object_store_id, name, key_path,
      auto_increment, &object_store_metadata);

  if (!s.ok()) {
    ReportErrorWithDetails(s, "Internal error creating object store.");
    return;
  }

  AddObjectStore(std::move(object_store_metadata), object_store_id);
  transaction->ScheduleAbortTask(
      base::BindOnce(&IndexedDBDatabase::CreateObjectStoreAbortOperation, this,
                     object_store_id));
}
