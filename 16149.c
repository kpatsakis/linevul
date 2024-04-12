void HTMLMediaElement::UpdateControlsVisibility() {
  if (!isConnected())
    return;

  bool native_controls = ShouldShowControls(RecordMetricsBehavior::kDoRecord);

  if (!RuntimeEnabledFeatures::LazyInitializeMediaControlsEnabled() ||
      RuntimeEnabledFeatures::MediaCastOverlayButtonEnabled() ||
      native_controls) {
    EnsureMediaControls();

    GetMediaControls()->Reset();
  }

  if (native_controls)
    GetMediaControls()->MaybeShow();
  else if (GetMediaControls())
    GetMediaControls()->Hide();

  if (web_media_player_)
    web_media_player_->OnHasNativeControlsChanged(native_controls);
}
