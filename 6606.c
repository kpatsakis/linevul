String MediaControlTextTrackListElement::getTextTrackLabel(TextTrack* track) {
  if (!track) {
    return mediaElement().locale().queryString(
        WebLocalizedString::TextTracksOff);
  }

  String trackLabel = track->label();

  if (trackLabel.isEmpty())
    trackLabel = track->language();

  if (trackLabel.isEmpty()) {
    trackLabel = String(mediaElement().locale().queryString(
        WebLocalizedString::TextTracksNoLabel,
        String::number(track->trackIndex() + 1)));
  }

  return trackLabel;
}
