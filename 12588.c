void BrowserMainLoop::SynchronouslyFlushStartupTasks() {
  startup_task_runner_->RunAllTasksNow();
}
