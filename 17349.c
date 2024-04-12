void MultibufferDataSource::SetPreload(Preload preload) {
  DVLOG(1) << __func__ << "(" << preload << ")";
  DCHECK(render_task_runner_->BelongsToCurrentThread());
  preload_ = preload;
  UpdateBufferSizes();
}
