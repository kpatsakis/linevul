IndexedDBTransaction::~IndexedDBTransaction() {
  IDB_ASYNC_TRACE_END("IndexedDBTransaction::lifetime", this);
  DCHECK_EQ(state_, FINISHED);
  DCHECK(preemptive_task_queue_.empty());
  DCHECK_EQ(pending_preemptive_events_, 0);
  DCHECK(task_queue_.empty());
  DCHECK(abort_task_stack_.empty());
  DCHECK(!processing_event_queue_);
}
