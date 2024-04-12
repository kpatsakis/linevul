 bool MediaControlVolumeSliderElement::willRespondToMouseMoveEvents() {
  if (!isConnected() || !document().isActive())
    return false;

  return MediaControlInputElement::willRespondToMouseMoveEvents();
}
