void TextTrack::setMode(const AtomicString& mode) {
  DCHECK(mode == DisabledKeyword() || mode == HiddenKeyword() ||
         mode == ShowingKeyword());

  if (mode_ == mode)
    return;

  if (cues_ && GetCueTimeline()) {
    if (mode == DisabledKeyword())
      GetCueTimeline()->RemoveCues(this, cues_.Get());
    else if (mode != ShowingKeyword())
      GetCueTimeline()->HideCues(this, cues_.Get());
  }

  mode_ = mode;

  if (mode != DisabledKeyword() && GetReadinessState() == kLoaded) {
    if (cues_ && GetCueTimeline())
      GetCueTimeline()->AddCues(this, cues_.Get());
  }

  if (MediaElement())
    MediaElement()->TextTrackModeChanged(this);
}
