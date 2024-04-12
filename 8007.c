void HTMLMediaElement::pause() {
  BLINK_MEDIA_LOG << "pause(" << (void*)this << ")";

  autoplay_policy_->StopAutoplayMutedWhenVisible();
  PauseInternal();
}
