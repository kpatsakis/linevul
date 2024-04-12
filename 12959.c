void TextTrackCue::CueWillChange() {
  if (track_)
    track_->CueWillChange(this);
}
