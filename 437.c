void HTMLMediaElement::ConfigureTextTrackDisplay() {
  DCHECK(text_tracks_);
  BLINK_MEDIA_LOG << "configureTextTrackDisplay(" << (void*)this << ")";

  if (processing_preference_change_)
    return;

  bool have_visible_text_track = text_tracks_->HasShowingTracks();
  text_tracks_visible_ = have_visible_text_track;

  if (!have_visible_text_track && !GetMediaControls())
    return;

  GetCueTimeline().UpdateActiveCues(currentTime());

  UpdateTextTrackDisplay();
}
