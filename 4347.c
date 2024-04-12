double HTMLMediaElement::currentTime() const {
  if (default_playback_start_position_)
    return default_playback_start_position_;

  if (seeking_) {
    BLINK_MEDIA_LOG << "currentTime(" << (void*)this
                    << ") - seeking, returning " << last_seek_time_;
    return last_seek_time_;
  }

  return OfficialPlaybackPosition();
}
