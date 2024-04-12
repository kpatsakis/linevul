TaskQueueManager* SchedulerHelper::GetTaskQueueManagerForTesting() {
  CheckOnValidThread();
  return task_queue_manager_.get();
 }
