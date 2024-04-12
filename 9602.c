RendererSchedulerImpl::InputTaskRunner() {
  helper_.CheckOnValidThread();
  return input_task_queue_;
}
