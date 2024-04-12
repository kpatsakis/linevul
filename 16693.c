void LockScreenMediaControlsView::SetIsPlaying(bool playing) {
  MediaSessionAction action =
      playing ? MediaSessionAction::kPause : MediaSessionAction::kPlay;

  play_pause_button_->SetToggled(!playing);
  play_pause_button_->set_tag(static_cast<int>(action));

  UpdateActionButtonsVisibility();
}
