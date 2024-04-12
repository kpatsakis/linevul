void LockScreenMediaControlsView::MediaSessionPositionChanged(
    const base::Optional<media_session::MediaPosition>& position) {
  if (hide_controls_timer_->IsRunning())
    return;

  position_ = position;

  if (!position.has_value()) {
    if (progress_->GetVisible()) {
      progress_->SetVisible(false);
      Layout();
    }
    return;
  }

  progress_->UpdateProgress(*position);

  if (!progress_->GetVisible()) {
    progress_->SetVisible(true);
    Layout();
  }
}
