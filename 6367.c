void HTMLMediaElement::PlaybackStateChanged() {
  BLINK_MEDIA_LOG << "playbackStateChanged(" << (void*)this << ")";

  if (!GetWebMediaPlayer())
    return;

  if (GetWebMediaPlayer()->Paused())
    PauseInternal();
  else
    PlayInternal();
}
