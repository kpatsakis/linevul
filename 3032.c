double WebMediaPlayerImpl::CurrentTime() const {
  DCHECK(main_task_runner_->BelongsToCurrentThread());
  DCHECK_NE(ready_state_, WebMediaPlayer::kReadyStateHaveNothing);

  return (ended_ && !std::isinf(Duration()))
             ? Duration()
             : GetCurrentTimeInternal().InSecondsF();
}
