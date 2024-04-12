void TaskManagerView::WindowClosing() {
  if (instance_ == this)
    instance_ = NULL;
  task_manager_->OnWindowClosed();
}
