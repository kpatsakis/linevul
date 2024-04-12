void HTMLMediaElement::RemoveVideoTrack(WebMediaPlayer::TrackId track_id) {
  BLINK_MEDIA_LOG << "removeVideoTrack(" << (void*)this << ")";

  videoTracks().Remove(track_id);
}
