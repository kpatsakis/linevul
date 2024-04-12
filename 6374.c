void HTMLMediaElement::setVolume(double vol, ExceptionState& exceptionState) {
  BLINK_MEDIA_LOG << "setVolume(" << (void*)this << ", " << vol << ")";

  if (m_volume == vol)
    return;

  if (vol < 0.0f || vol > 1.0f) {
    exceptionState.throwDOMException(
        IndexSizeError,
        ExceptionMessages::indexOutsideRange(
            "volume", vol, 0.0, ExceptionMessages::InclusiveBound, 1.0,
            ExceptionMessages::InclusiveBound));
    return;
  }

  m_volume = vol;

  if (webMediaPlayer())
    webMediaPlayer()->setVolume(effectiveMediaVolume());
  scheduleEvent(EventTypeNames::volumechange);
}
