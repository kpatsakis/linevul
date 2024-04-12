bool MediaControlVolumeSliderElement::keepEventInNode(Event* event) {
  return isUserInteractionEventForSlider(event, layoutObject());
}
