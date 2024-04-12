void BackendImpl::CriticalError(int error) {
  STRESS_NOTREACHED();
  LOG(ERROR) << "Critical error found " << error;
  if (disabled_)
    return;

  stats_.OnEvent(Stats::FATAL_ERROR);
  LogStats();
  ReportError(error);

  data_->header.table_len = 1;
  disabled_ = true;

  if (!num_refs_)
    base::ThreadTaskRunnerHandle::Get()->PostTask(
        FROM_HERE, base::Bind(&BackendImpl::RestartCache, GetWeakPtr(), true));
}
