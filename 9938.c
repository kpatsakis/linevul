  CurrentThreadMock()
      : task_runner_delegate_(
            scheduler::LazySchedulerMessageLoopDelegateForTests::Create()),
        scheduler_(
            new scheduler::RendererSchedulerImpl(task_runner_delegate_.get())),
        web_scheduler_(
            new scheduler::RendererWebSchedulerImpl(scheduler_.get())),
        web_task_runner_(
            new scheduler::WebTaskRunnerImpl(scheduler_->DefaultTaskRunner())) {
  }
