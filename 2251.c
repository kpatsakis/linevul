bool WatchDogThread::PostDelayedTask(const tracked_objects::Location& from_here,
                                     const base::Closure& task,
                                     base::TimeDelta delay) {
  return PostTaskHelper(from_here, task, delay);
}
