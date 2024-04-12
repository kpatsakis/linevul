void HTMLMediaElement::updateTextTrackDisplay() {
  BLINK_MEDIA_LOG << "updateTextTrackDisplay(" << (void*)this << ")";

  ensureTextTrackContainer().updateDisplay(
      *this, TextTrackContainer::DidNotStartExposingControls);
}
