 void WorkerProcessLauncher::Core::OnChannelError() {
  DCHECK(caller_task_runner_->BelongsToCurrentThread());

  ipc_error_timer_->Start(FROM_HERE, base::TimeDelta::FromSeconds(5),
                          this, &Core::StopWorker);
}
