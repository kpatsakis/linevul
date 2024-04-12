void DesktopSessionWin::OnSessionDetached() {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  DCHECK(launcher_.get() != NULL);

  launcher_.reset();
}
