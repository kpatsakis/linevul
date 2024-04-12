 void MultibufferDataSource::MediaPlaybackRateChanged(double playback_rate) {
  DCHECK(render_task_runner_->BelongsToCurrentThread());

  if (playback_rate < 0.0)
    return;

  playback_rate_ = playback_rate;
  cancel_on_defer_ = false;
  UpdateBufferSizes();
}
