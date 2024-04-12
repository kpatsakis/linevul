void HTMLMediaElement::setCurrentTime(double time) {
  if (ready_state_ == kHaveNothing) {
    default_playback_start_position_ = time;
    return;
  }

  Seek(time);
}
