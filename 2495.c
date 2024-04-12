void ThreadWatcher::OnCheckResponsiveness(uint64 ping_sequence_number) {
  DCHECK(WatchDogThread::CurrentlyOnWatchDogThread());
  if (!active_) {
    responsive_ = true;
    return;
  }
  if (ping_sequence_number_ != ping_sequence_number) {
    ResetHangCounters();

    responsive_ = true;
    return;
  }
  GotNoResponse();

  base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
      FROM_HERE,
      base::Bind(&ThreadWatcher::OnCheckResponsiveness,
                 weak_ptr_factory_.GetWeakPtr(), ping_sequence_number_),
      unresponsive_time_);
  responsive_ = false;
}
