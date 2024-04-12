void HTMLMediaElement::setMuted(bool muted) {
  BLINK_MEDIA_LOG << "setMuted(" << (void*)this << ", " << boolString(muted)
                  << ")";

  if (m_muted == muted)
    return;

  bool wasAutoplayingMuted = isAutoplayingMuted();
  bool wasPendingAutoplayMuted = m_autoplayVisibilityObserver && paused() &&
                                 m_muted && isLockedPendingUserGesture();

  if (UserGestureIndicator::processingUserGesture())
    unlockUserGesture();

  m_muted = muted;

  scheduleEvent(EventTypeNames::volumechange);

  if (wasAutoplayingMuted) {
    if (isGestureNeededForPlayback()) {
      pause();
      m_autoplayUmaHelper->recordAutoplayUnmuteStatus(
          AutoplayUnmuteActionStatus::Failure);
    } else {
      m_autoplayUmaHelper->recordAutoplayUnmuteStatus(
          AutoplayUnmuteActionStatus::Success);
    }
  }

  if (webMediaPlayer())
    webMediaPlayer()->setVolume(effectiveMediaVolume());

  if (wasPendingAutoplayMuted) {
    m_autoplayVisibilityObserver->stop();
    m_autoplayVisibilityObserver = nullptr;
  }
}
