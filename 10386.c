IndexedDBTransaction::Operation IndexedDBTransaction::TaskQueue::pop() {
  DCHECK(!queue_.empty());
  Operation task = std::move(queue_.front());
  queue_.pop();
  return task;
}
