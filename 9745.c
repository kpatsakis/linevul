void WtsSessionProcessDelegate::Core::InitializeJobCompleted(
    scoped_ptr<ScopedHandle> job) {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  DCHECK(!job_.IsValid());

  job_ = job->Pass();
 }
