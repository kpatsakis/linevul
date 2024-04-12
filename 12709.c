void IndexedDBDispatcher::RequestIDBDatabaseOpen(
      WebIDBDatabaseCallbacks* callbacks_ptr,
      int32 idb_database_id) {
  ResetCursorPrefetchCaches();
  scoped_ptr<WebIDBDatabaseCallbacks> callbacks(callbacks_ptr);

  DCHECK(!pending_database_callbacks_.Lookup(idb_database_id));
  pending_database_callbacks_.AddWithID(callbacks.release(), idb_database_id);
  Send(new IndexedDBHostMsg_DatabaseOpen(idb_database_id, CurrentWorkerId(),
                                         idb_database_id));
}
