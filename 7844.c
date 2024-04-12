bool WebMediaPlayerImpl::HasVideo() const {
  DCHECK(main_task_runner_->BelongsToCurrentThread());

  return pipeline_metadata_.has_video;
}
