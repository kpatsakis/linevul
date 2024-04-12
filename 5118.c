void SchedulerHelper::PumpQueue(size_t queue_index) {
  CheckOnValidThread();
  return task_queue_manager_->PumpQueue(queue_index);
}
