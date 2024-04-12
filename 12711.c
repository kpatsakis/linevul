void WebMediaPlayerImpl::Play() {
  DVLOG(1) << __func__;
  DCHECK(main_task_runner_->BelongsToCurrentThread());

  if (blink::WebUserGestureIndicator::IsProcessingUserGesture(frame_))
    video_locked_when_paused_when_hidden_ = false;

#if defined(OS_ANDROID)  // WMPI_CAST
  if (IsRemote()) {
    cast_impl_.play();
    return;
  }
#endif
  delegate_->SetIdle(delegate_id_, false);
  paused_ = false;
  pipeline_controller_.SetPlaybackRate(playback_rate_);
  background_pause_timer_.Stop();

  if (data_source_)
    data_source_->MediaIsPlaying();

  if (observer_)
    observer_->OnPlaying();

  watch_time_reporter_->SetAutoplayInitiated(client_->WasAutoplayInitiated());

  if (!Seeking()) {
    DCHECK(watch_time_reporter_);
    watch_time_reporter_->OnPlaying();
  }

  if (video_decode_stats_reporter_)
    video_decode_stats_reporter_->OnPlaying();

  media_log_->AddEvent(media_log_->CreateEvent(MediaLogEvent::PLAY));
  UpdatePlayState();
}
