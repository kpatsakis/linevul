void WorkerProcessLauncher::Core::Send(IPC::Message* message) {
  DCHECK(caller_task_runner_->BelongsToCurrentThread());

  if (ipc_enabled_) {
    launcher_delegate_->Send(message);
  } else {
    delete message;
  }
}
