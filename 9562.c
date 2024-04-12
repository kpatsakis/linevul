unsigned WebMediaPlayerImpl::DroppedFrameCount() const {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  return GetPipelineStatistics().video_frames_dropped;
}
