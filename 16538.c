int ResourceDispatcherHostImpl::MakeRequestID() {
  DCHECK(io_thread_task_runner_->BelongsToCurrentThread());
  return --request_id_;
}
