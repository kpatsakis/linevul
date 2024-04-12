void RendererSchedulerImpl::VirtualTimePaused() {
  for (const auto& pair : task_runners_) {
    if (pair.first->queue_class() == MainThreadTaskQueue::QueueClass::kTimer) {
      DCHECK(!task_queue_throttler_->IsThrottled(pair.first.get()));
      DCHECK(!pair.first->HasActiveFence());
      pair.first->InsertFence(TaskQueue::InsertFencePosition::kNow);
    }
  }
  for (auto& observer : main_thread_only().virtual_time_observers) {
    observer.OnVirtualTimePaused(virtual_time_domain_->Now() -
                                 main_thread_only().initial_virtual_time);
  }
}
