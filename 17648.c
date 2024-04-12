void IndexedDBCursor::PrefetchContinue(
    int number_to_fetch,
    scoped_refptr<IndexedDBCallbacks> callbacks) {
  IDB_TRACE("IndexedDBCursor::PrefetchContinue");

  if (closed_) {
    callbacks->OnError(CreateCursorClosedError());
    return;
  }

  transaction_->ScheduleTask(
      task_type_,
      BindWeakOperation(&IndexedDBCursor::CursorPrefetchIterationOperation,
                        ptr_factory_.GetWeakPtr(), number_to_fetch, callbacks));
}
