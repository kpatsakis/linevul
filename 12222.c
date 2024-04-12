bool WatchDogThread::PostTask(const tracked_objects::Location& from_here,
                              const base::Closure& task) {
  return PostTaskHelper(from_here, task, base::TimeDelta());
}
