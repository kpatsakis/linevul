void TaskQueueManager::RemoveTaskObserver(
    base::MessageLoop::TaskObserver* task_observer) {
  DCHECK(main_thread_checker_.CalledOnValidThread());
  main_task_runner_->RemoveTaskObserver(task_observer);
  task_observers_.RemoveObserver(task_observer);
 }
