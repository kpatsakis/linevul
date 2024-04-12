  void ScheduleUserCallback(int result) {
    base::ThreadTaskRunnerHandle::Get()->PostTask(
        FROM_HERE,
        base::BindOnce(&MockResponseReader::InvokeUserCompletionCallback,
                       weak_factory_.GetWeakPtr(), result));
  }
