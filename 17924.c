void IndexedDBDispatcher::OnSuccessCursorPrefetch(
    const IndexedDBMsg_CallbacksSuccessCursorPrefetch_Params& p) {
  DCHECK_EQ(p.thread_id, CurrentWorkerId());
  int32 response_id = p.response_id;
  int32 cursor_id = p.cursor_id;
  const std::vector<IndexedDBKey>& keys = p.keys;
  const std::vector<IndexedDBKey>& primary_keys = p.primary_keys;
  const std::vector<content::SerializedScriptValue>& values = p.values;
  RendererWebIDBCursorImpl* cursor = cursors_[cursor_id];
  DCHECK(cursor);
  cursor->SetPrefetchData(keys, primary_keys, values);

  WebIDBCallbacks* callbacks = pending_callbacks_.Lookup(response_id);
  DCHECK(callbacks);
  cursor->CachedContinue(callbacks);
  pending_callbacks_.Remove(response_id);
}
