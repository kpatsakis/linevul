void IndexedDBDispatcher::RequestIDBObjectStoreDelete(
    const IndexedDBKey& key,
    WebIDBCallbacks* callbacks_ptr,
    int32 idb_object_store_id,
    const WebIDBTransaction& transaction,
    WebExceptionCode* ec) {
  ResetCursorPrefetchCaches();
  scoped_ptr<WebIDBCallbacks> callbacks(callbacks_ptr);

  int32 response_id = pending_callbacks_.Add(callbacks.release());
  Send(new IndexedDBHostMsg_ObjectStoreDelete(
      idb_object_store_id, CurrentWorkerId(), response_id, key,
      TransactionId(transaction), ec));
  if (*ec)
    pending_callbacks_.Remove(response_id);
}
