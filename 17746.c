void WebMediaPlayerImpl::OnFirstFrame(base::TimeTicks frame_time) {
  DCHECK(!load_start_time_.is_null());
  DCHECK(!skip_metrics_due_to_startup_suspend_);
  has_first_frame_ = true;
  const base::TimeDelta elapsed = frame_time - load_start_time_;
  media_metrics_provider_->SetTimeToFirstFrame(elapsed);
  RecordTimingUMA("Media.TimeToFirstFrame", elapsed);
}
