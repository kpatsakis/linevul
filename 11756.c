void IndexedDBTransaction::TaskQueue::clear() {
  while (!queue_.empty())
    queue_.pop();
}
