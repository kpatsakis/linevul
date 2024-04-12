QuotaThreadTask::QuotaThreadTask(
    QuotaTaskObserver* observer,
    TaskRunner* target_task_runner)
    : QuotaTask(observer),
      target_task_runner_(target_task_runner) {
}
