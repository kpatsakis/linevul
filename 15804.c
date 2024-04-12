bool WebMediaPlayerImpl::Paused() const {
  DCHECK(main_task_runner_->BelongsToCurrentThread());

#if defined(OS_ANDROID)  // WMPI_CAST
  if (IsRemote())
    return cast_impl_.IsPaused();
#endif

  return pipeline_controller_.GetPlaybackRate() == 0.0f;
}
