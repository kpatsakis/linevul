bool MessageLoop::SweepDelayedWorkQueueAndReturnTrueIfStillHasWork() {
  while (!delayed_work_queue_.empty()) {
    const PendingTask& pending_task = delayed_work_queue_.top();
    if (!pending_task.task.IsCancelled())
      return true;

#if defined(OS_WIN)
    DecrementHighResTaskCountIfNeeded(pending_task);
#endif
    delayed_work_queue_.pop();
  }
  return false;
}
